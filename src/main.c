#include <globals.h>
#include <stdbool.h>
#include <lib/types.h>
#include "asset.h"
#include "controller.h"
#include "display.h"
#include "dragonfs.h"
#include "dz_actor.h"
#include "fonts.h"
#include "graphics.h"
#include "joypad.h"
#include "n64sys.h"
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_font.h"
#include "rdpq_text.h"
#include "t3d/t3d.h"
#include "t3d/t3dmath.h"
#include <t3d/t3dmodel.h>
#include <libdragon.h>

void main_init();
void main_destroy();

int main() {
  main_init();

  // setting up the camera
  T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
  t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(60.0f), 0.1f, 1000.0f);
  float camera_dist = 30.0f;
  Vec3 camera_pos = {{camera_dist, 5.0f, 0}}; // start 40 units away from model
  Vec3 camera_target = {{0, 0, 0}};
  Vec3 camera_up = {{0, 1, 0}};
  t3d_viewport_look_at(&viewport, &camera_pos, &camera_target, &camera_up);

  // lighting
  u8 ambient_light[4] = {80, 80, 80, 0xFF};
  u8 light_direction[4] = {0xEE, 0xAA, 0xAA, 0xFF};
  Vec3 light_dir_vec = {{-1.0f, 1.0f, 1.0f}};
  t3d_vec3_norm(&light_dir_vec);

  // TODO: temporary actorCtx until I implement PlayState
  ActorContext* actorCtx = ActorContext_Init();
  Actor_Spawn(actorCtx, ACTOR_OBJ_N64LOGO, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

  // initialize font
  rdpq_font_t* lexis_font = rdpq_font_load("rom:/lexis.font64");
  rdpq_text_register_font(FONTID_LEXIS, lexis_font);

  for (;;) {
    rdpq_attach(display_get(), display_get_zbuf());
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    t3d_screen_clear_color(RGBA32(80, 80, 80, 0xFF));
    t3d_screen_clear_depth();
 
    // lighting
    t3d_light_set_ambient(ambient_light);
    t3d_light_set_directional(0, light_direction, &light_dir_vec);
    t3d_light_set_count(1);

    Actor_UpdateAll(actorCtx);
    rdpq_text_printf(NULL, FONTID_LEXIS, 10.0f, 10.0f,
                     "FPS: %.02f\nHEAP_START: %p", display_get_fps(), HEAP_START_ADDR);

    rdpq_detach_show();
  }

  main_destroy();

  return 0;
}

void main_init() {
  // some of our assets use level 2 compression
  asset_init_compression(2);
  dfs_init(DFS_DEFAULT_LOCATION);
  display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE);
  rdpq_init();
  t3d_init((T3DInitParams) {});
  joypad_init();
}

void main_destroy() {
  joypad_close();
  t3d_destroy();
  rdpq_close();
  display_close();
  dfs_close(DFS_DEFAULT_LOCATION);
}
