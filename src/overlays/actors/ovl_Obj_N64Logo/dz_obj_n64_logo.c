#include "dz_obj_n64_logo.h"
#include <dz_actor.h>
#include <globals.h>
#include "joypad.h"
#include <lib/types.h>
#include <lib/dzmath.h>
#include "n64sys.h"
#include "t3d/t3dmath.h"
#include <t3d/t3dmodel.h>

void ObjN64Logo_Init(Actor* thisx);
void ObjN64Logo_Update(Actor* thisx);
void ObjN64Logo_Draw(Actor* thisx);
void ObjN64Logo_Destroy(Actor* thisx);

static T3DModel* n64_model;

// the model matrix (4x4 fixed-point)
float model_scale[3] = {0.1f, 0.1f, 0.1f};
float model_position[3] = {0.0f, 0.0f, 0.0f};
float model_rotation[3] = {0.0f, 0.0f, 0.0f};

// @TODO: must replace this with the state's frames
static u8 frameIdx = 0;

ActorProfile ObjN64Logo_Profile = {
  ACTOR_OBJ_N64LOGO,
  sizeof(ObjN64Logo),
  (ActorFunc)ObjN64Logo_Init,
  (ActorFunc)ObjN64Logo_Update,
  (ActorFunc)ObjN64Logo_Draw,
  (ActorFunc)ObjN64Logo_Destroy,
};

void ObjN64Logo_Init(Actor* thisx) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;

  this->mat4fp = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT);
  this->dplDraw = NULL;
  n64_model = t3d_model_load(N64_MODEL_FILENAME);
}

static binang bob = 0;

void ObjN64Logo_Update(Actor* thisx) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;
  int input_axis[2] = { // TODO: must replace this later with playState's global input
    joypad_get_axis_held(JOYPAD_PORT_1, JOYPAD_AXIS_STICK_Y),
    joypad_get_axis_held(JOYPAD_PORT_1, JOYPAD_AXIS_STICK_X),
  };

  model_position[0] += input_axis[0] * -0.5f;
  model_position[2] += input_axis[1] * -0.5f;

  frameIdx = (frameIdx + 1) % FB_COUNT;
  bob += 512;
  model_position[1] = dz_sin(bob) * 2.0f;
  model_rotation[1] += 0.02f;
  t3d_mat4fp_from_srt_euler(&this->mat4fp[frameIdx], model_scale, model_rotation, model_position);
}

void ObjN64Logo_Draw(Actor* thisx) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;

    if (!this->dplDraw) {
      rspq_block_begin();
      t3d_model_draw(n64_model);
      t3d_matrix_pop(1);
      this->dplDraw = rspq_block_end();
    }
    t3d_matrix_push(&this->mat4fp[frameIdx]);
    rspq_block_run(this->dplDraw);
}

void ObjN64Logo_Destroy(Actor* thisx) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;
  t3d_model_free(n64_model);
}
