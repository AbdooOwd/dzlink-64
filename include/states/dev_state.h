#ifndef DEV_STATE_H
#define DEV_STATE_H

#include "dz_actor.h"

typedef struct DevState {
  ActorContext* actorCtx;
} DevState;


void DevState_Init(void* state);
void DevState_Main(void* state);
void DevState_Destroy(void* state);

#endif
