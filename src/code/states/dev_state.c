#include "dz_actor.h"
#include <states/dev_state.h>
#include <t3d/t3d.h>
#include <globals.h>

T3DViewport viewport;
u8 ambient_light[4] = {80, 80, 80, 0xFF};
u8 light_direction[4] = {0xEE, 0xAA, 0xAA, 0xFF};
Vec3 light_dir_vec = {{-1.0f, 1.0f, 1.0f}};

void DevState_Init(void* state) {
  DevState* this = (DevState*) state;

  t3d_init((T3DInitParams){});

  viewport = t3d_viewport_create_buffered(FB_COUNT);
  t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(60.0f), 5.0f, 80.0f);
  float camera_dist = 30.0f;
  Vec3 camera_pos = {{camera_dist, 9.0f, 0}}; // start 40 units away from model
  Vec3 camera_target = {{0, 0, 0}};
  Vec3 camera_up = {{0, 1, 0}};
  t3d_viewport_look_at(&viewport, &camera_pos, &camera_target, &camera_up);
  t3d_viewport_attach(&viewport);

  t3d_vec3_norm(&light_dir_vec);
 
  // lighting
  t3d_light_set_ambient(ambient_light);
  t3d_light_set_directional(0, light_direction, &light_dir_vec);
  t3d_light_set_count(1);

  this->actorCtx = ActorContext_Init();
  Actor_Spawn(this->actorCtx, ACTOR_OBJ_N64LOGO, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});
}

void DevState_Main(void* state) {
  DevState* this = (DevState*) state;

  t3d_frame_start();

  t3d_screen_clear_color(RGBA32(80, 80, 80, 0xFF));
  t3d_screen_clear_depth();

  Actor_UpdateAll(this->actorCtx);
}

void DevState_Destroy(void* state) {
  DevState* this = (DevState*) state;

  ActorContext_Destroy(this->actorCtx);
  t3d_destroy();
}

