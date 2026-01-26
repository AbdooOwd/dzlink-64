#include <fonts.h>
#include <lib/types.h>
#include <game.h>
#include <video/dz_display.h>
#include <globals.h>
#include <states/play_state.h>
#include <lib/dzmath.h>

#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include "display.h"
#include "rdpq_text.h"
#include "joypad.h"


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
    display_switch_widescreen(&gMasterState.displaySettings);
    display_update_settings(&gMasterState.displaySettings, &this->camera);
  }

  if (joypad_get_buttons_pressed(JOYPAD_DEFAULT_PORT).r) {
    display_switch_antialiasing(&gMasterState.displaySettings);
    display_update_settings(&gMasterState.displaySettings, NULL);
  }

  t3d_frame_start();

  t3d_screen_clear_color(RGBA32(80, 80, 80, 0xFF));
  t3d_screen_clear_depth();

  Actor_UpdateAll(this->actorCtx, this);

  binang camYaw = this->camera.yaw;

  Camera_Rotate(&this->camera, input->cstick_x * 5.0f, input->cstick_y * -5.0f);
  Camera_TranslateFree(&this->camera, &VEC3(
    (dz_cos(camYaw) * input->stick_x + dz_sin(camYaw) * input->stick_y) * 0.01f,
    0,
    (-dz_cos(camYaw) * input->stick_y + dz_sin(camYaw) * input->stick_x) * 0.01f
  ));

  Camera_Attach(&this->camera);

  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10, 20.0f, "Yaw: %i\nPitch: %i", this->camera.yaw, this->camera.pitch);
  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10.0f, display_get_height() - 20,
                   "Press L for widescreen (Currently: %i)\nPress R for Anti-Aliasing (Currently: %i)",
                   display_widescreen_enabled(&gMasterState.displaySettings),
                   display_antialiasing_enabled(&gMasterState.displaySettings));

}

void PlayState_Destroy(void* state) {
  PlayState* this = (PlayState*) state;

  ActorContext_Destroy(this->actorCtx);
  t3d_destroy();
}

