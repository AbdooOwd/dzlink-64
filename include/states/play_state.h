#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "dz_actor.h"
#include <camera.h>

typedef struct PlayState {
  ActorContext* actorCtx;
  Camera camera;
} PlayState;


void PlayState_Init(void* state);
void PlayState_Main(void* state);
void PlayState_Destroy(void* state);

#endif
