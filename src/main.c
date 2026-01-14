#include <stdbool.h>
#include "console.h"
#include "include/types.h"
#include "asset.h"
#include "display.h"
#include "dragonfs.h"
#include "graphics.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rspq.h"
#include "t3d/t3d.h"
#include "t3d/t3dmath.h"
#include <t3d/t3dmodel.h>
#include <libdragon.h>

#define FB_COUNT  3

int main() {
  // some of our assets use level 2 compression
  asset_init_compression(2);
  dfs_init(DFS_DEFAULT_LOCATION);
  display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
  rdpq_init();
  t3d_init((T3DInitParams) {});

  T3DModel* model = t3d_model_load("rom:/n64.t3dm");

  // setting up the camera
  T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
  t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(60.0f), 0.1f, 1000.0f);
  float camera_dist = 30.0f;
  T3DVec3 camera_pos = {{camera_dist, 5.0f, 0}}; // start 40 units away from model
  T3DVec3 camera_target = {{0, 0, 0}};
  T3DVec3 camera_up = {{0, 1, 0}};
  t3d_viewport_look_at(&viewport, &camera_pos, &camera_target, &camera_up);

  // the model matrix (4x4 fixed-point)
  T3DMat4FP* mat4fp = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT);
  float model_scale[3] = {0.1f, 0.1f, 0.1f};
  float model_position[3] = {0.0f, 0.0f, 0.0f};
  float model_rotation[3] = {0.0f, 0.0f, 0.0f};

  // lighting
  u8 ambient_light[4] = {80, 80, 80, 0xFF};
  u8 light_direction[4] = {0xEE, 0xAA, 0xAA, 0xFF};
  T3DVec3 light_dir_vec = {{-1.0f, 1.0f, 1.0f}};
  t3d_vec3_norm(&light_dir_vec);

  u8 frameIdx = 0;
  rspq_block_t* dplDraw = NULL;

  for (;;) {
    frameIdx = (frameIdx + 1) % FB_COUNT;

    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    t3d_screen_clear_color(RGBA32(80, 80, 80, 0xFF));
    t3d_screen_clear_depth();

    model_rotation[1] += 0.02f;
    t3d_mat4fp_from_srt_euler(&mat4fp[frameIdx], model_scale, model_rotation, model_position);

    // lighting
    t3d_light_set_ambient(ambient_light);
    t3d_light_set_directional(0, light_direction, &light_dir_vec);
    t3d_light_set_count(1);

    if (!dplDraw) {
      rspq_block_begin();
      t3d_model_draw(model);
      t3d_matrix_pop(1);
      dplDraw = rspq_block_end();
    }

    t3d_matrix_push(&mat4fp[frameIdx]);
    rspq_block_run(dplDraw);
    rdpq_detach_show();
  }

  t3d_destroy();

  return 0;
}
