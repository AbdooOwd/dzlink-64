#include "{{ActorFilename}}.h"
#include <globals.h>
#include <game.h>
#include <states/play_state.h>

void {{ActorName}}_Init(Actor* thisx, PlayState* play);
void {{ActorName}}_Update(Actor* thisx, PlayState* play);
void {{ActorName}}_Draw(Actor* thisx, PlayState* play);
void {{ActorName}}_Destroy(Actor* thisx, PlayState* play);

ActorProfile {{ActorName}}_Profile = {
  {{ActorEnumID}},
  sizeof({{ActorName}}),
  (ActorFunc){{ActorName}}_Init,
  (ActorFunc){{ActorName}}_Update,
  (ActorFunc){{ActorName}}_Draw,
  (ActorFunc){{ActorName}}_Destroy,
};

void {{ActorName}}_Init(Actor* thisx, PlayState* play) {
  {{ActorName}}* this = ({{ActorName}}*) thisx;

  this->mat4fp = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT);
  this->dplDraw = NULL;
}

void {{ActorName}}_Update(Actor* thisx, PlayState* play) {
  {{ActorName}}* this = ({{ActorName}}*) thisx;

}

void {{ActorName}}_Draw(Actor* thisx, PlayState* play) {
  {{ActorName}}* this = ({{ActorName}}*) thisx;

    t3d_mat4fp_from_srt_euler(&this->mat4fp[gMasterState.frameIdx],
                            (const float*) &this->actor.scale.v, (const float*) &this->actor.world.rot.v,
                            (const float*) &this->actor.world.pos.v);

    if (!this->dplDraw) {
      rspq_block_begin();
      /* --- INSERT MODEL DRAWING HERE --- */
      t3d_matrix_pop(1);
      this->dplDraw = rspq_block_end();
    }
    t3d_matrix_push(&this->mat4fp[gMasterState.frameIdx]);
    rspq_block_run(this->dplDraw);
}

void {{ActorName}}_Destroy(Actor* thisx, PlayState* play) {
  {{ActorName}}* this = ({{ActorName}}*) thisx;
  /* --- FREE MODEL HERE --- */
}
