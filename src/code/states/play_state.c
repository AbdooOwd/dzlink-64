#include <camera.h>
#include "display.h"
#include <dz_actor.h>
#include <fonts.h>
#include <lib/types.h>
#include <lib/utils.h>
#include "game.h"
#include "joypad.h"
#include "rdpq_text.h"
#include "t3d/t3dmath.h"
#include <video/dz_display.h>
#include <t3d/t3d.h>
#include <globals.h>
#include <states/play_state.h>
#include <lib/dzmath.h>

u8 ambient_light[4] = {80, 80, 80, 0xFF};
u8 light_direction[4] = {0xEE, 0xAA, 0xAA, 0xFF};
Vec3 light_dir_vec = {{-1.0f, 1.0f, 1.0f}};

void PlayState_Init(void* state) {
  PlayState* this = (PlayState*) state;

  t3d_init((T3DInitParams){});

  Camera_Spawn(&this->camera, VEC3(0, 15.0f, 0), 0, 0, VEC3_ZERO, CAMERA_DEFAULT_FOV);

  t3d_vec3_norm(&light_dir_vec);
 
  // lighting
  t3d_light_set_ambient(ambient_light);
  t3d_light_set_directional(0, light_direction, &light_dir_vec);
  t3d_light_set_count(1);

  this->actorCtx = ActorContext_Init();
  Actor_Spawn(this->actorCtx, this, ACTOR_OBJ_N64LOGO, VEC3(0, 0, -20.0f), VEC3_ZERO);
}

void PlayState_Main(void* state) {
  PlayState* this = (PlayState*) state;
  Input* input = &gMasterState.input;


  if (joypad_get_buttons_pressed(JOYPAD_DEFAULT_PORT).l) {
    display_switch_widescreen();
  }

  t3d_frame_start();

  t3d_screen_clear_color(RGBA32(80, 80, 80, 0xFF));
  t3d_screen_clear_depth();

  Actor_UpdateAll(this->actorCtx, this);

  Camera_Rotate(&this->camera, input->stick_x * 3.0f, input->stick_y * 3.0f);
  Camera_TranslateFree(&this->camera, &VEC3(input->cstick_x * 0.01f, 0, input->cstick_y * 0.01f));
  Camera_Attach(&this->camera);

  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10.0f, 10.0f, "FPS: %.02f", display_get_fps());
  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10.0f, 20.0f, "Aspect Ratio: %.02f", Camera_GetAspectRatio(&this->camera));
  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10.0f, display_get_height() - 10.0f, "Press L for widescreen");
}

void PlayState_Destroy(void* state) {
  PlayState* this = (PlayState*) state;

  ActorContext_Destroy(this->actorCtx);
  t3d_destroy();
}

