#ifndef ACTOR_OVERLAY_H
#define ACTOR_OVERLAY_H

#include "dz_actor.h"
#include "types.h"

typedef struct ActorOverlay {
  ActorProfile* profile;
  u8 numLoaded; // number of loaded instances of the actor
} ActorOverlay;

/* 
* each entry corresponds to one actor.
* thus, the length of this table is the same
* as the number of actor IDs
*/
extern ActorOverlay gActorOverlayTable[ACTOR_ID_MAX];

#endif
