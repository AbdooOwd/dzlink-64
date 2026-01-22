#include "dz_obj_n64_logo.h"
#include <dz_actor.h>
#include <globals.h>
#include <game.h>
#include <lib/types.h>
#include <lib/dzmath.h>
#include "n64sys.h"
#include <states/play_state.h>
#include "t3d/t3dmath.h"
#include <t3d/t3dmodel.h>

void ObjN64Logo_Init(Actor* thisx, PlayState* play);
void ObjN64Logo_Update(Actor* thisx, PlayState* play);
void ObjN64Logo_Draw(Actor* thisx, PlayState* play);
void ObjN64Logo_Destroy(Actor* thisx, PlayState* play);

static T3DModel* n64_model;

ActorProfile ObjN64Logo_Profile = {
  ACTOR_OBJ_N64LOGO,
  sizeof(ObjN64Logo),
  (ActorFunc)ObjN64Logo_Init,
  (ActorFunc)ObjN64Logo_Update,
  (ActorFunc)ObjN64Logo_Draw,
  (ActorFunc)ObjN64Logo_Destroy,
};

void ObjN64Logo_Init(Actor* thisx, PlayState* play) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;

  this->mat4fp = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT);
  this->dplDraw = NULL;
  n64_model = t3d_model_load(N64_MODEL_FILENAME);
}

static binang bob = 0;

void ObjN64Logo_Update(Actor* thisx, PlayState* play) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;

  this->actor.world.pos.y = this->actor.home.pos.y + dz_cos(bob) * 2.0f;
  bob += 512;

  t3d_mat4fp_from_srt_euler(&this->mat4fp[gMasterState.frameIdx],
                            (const float*) &this->actor.scale.v, (const float*) &this->actor.world.rot.v,
                            (const float*) &this->actor.world.pos.v);
}

void ObjN64Logo_Draw(Actor* thisx, PlayState* play) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;

    if (!this->dplDraw) {
      rspq_block_begin();
      t3d_model_draw(n64_model);
      t3d_matrix_pop(1);
      this->dplDraw = rspq_block_end();
    }
    t3d_matrix_push(&this->mat4fp[gMasterState.frameIdx]);
    rspq_block_run(this->dplDraw);
}

void ObjN64Logo_Destroy(Actor* thisx, PlayState* play) {
  ObjN64Logo* this = (ObjN64Logo*) thisx;
  t3d_model_free(n64_model);
}
