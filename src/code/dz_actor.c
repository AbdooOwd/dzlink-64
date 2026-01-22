#include "dz_actor_ovl.h"
#include "lib/types.h"
#include "n64sys.h"
#include <dz_actor.h>
#include <lib/utils.h>
#include <states/play_state.h>


ActorContext* ActorContext_Init() {
  ActorContext* actorCtx = malloc_uncached(sizeof(ActorContext));

  // we start at the first actor entry, also avoiding
  // the "none" actor ID
  ActorOverlay* overlayEntry = &gActorOverlayTable[0];

  // iterate to set their numLoaded to 0, because it's a new context
  for (u8 i = 0; i < ARRAY_COUNT(gActorOverlayTable); i++) {
    overlayEntry->numLoaded = 0;
    overlayEntry++; // NEXT ENTRY PLEASE!
  }

  return actorCtx;
}

void ActorContext_Destroy(ActorContext* actorCtx) {
  // @TODO: don't know if this works :shrugging_person:
  Actor* nextActor;
  for (u16 i = 0; i < actorCtx->total; i++) {
    nextActor = actorCtx->actorHead->next;
    free_uncached(actorCtx->actorHead);
    actorCtx->actorHead = nextActor;
  }
}

Actor* Actor_Spawn(ActorContext* actorCtx, PlayState* play, ActorID actor_id, Vec3 pos, Vec3 rot) {
  ActorOverlay* overlayEntry = &gActorOverlayTable[actor_id];
  ActorProfile* profile = overlayEntry->profile;

  Actor* newActor = malloc_uncached(profile->instance_size);

  assertf(newActor != NULL, "Couldn't allocate for new actor %i of size: %li", actor_id, profile->instance_size);

  overlayEntry->numLoaded++; // anouther actor instance was loaded

  if (actorCtx->actorHead == NULL) {
    actorCtx->actorHead = newActor;
    newActor->prev = NULL;
    newActor->next = NULL;
  } else {
    newActor->prev = NULL;
    newActor->next = actorCtx->actorHead;
    actorCtx->actorHead->prev = newActor;
    actorCtx->actorHead = newActor;
  }

  actorCtx->total++;

  newActor->overlayEntry = overlayEntry;
  newActor->id = profile->id;

  newActor->init = profile->init;
  newActor->update = profile->update;
  newActor->draw = profile->draw;
  newActor->destroy = profile->destroy;

  newActor->home.pos.x = pos.x;
  newActor->home.pos.y = pos.y;
  newActor->home.pos.z = pos.z;

  newActor->home.rot.x = rot.x;
  newActor->home.rot.y = rot.y;
  newActor->home.rot.z = rot.z;

  // @NOTE: cuz every model's scale on Blender is x10
  newActor->scale = (Vec3){{0.1f, 0.1f, 0.1f}};

  newActor->world = newActor->home;

  Actor_Init(newActor, play);

  return newActor;
}


void Actor_Init(Actor* actor, PlayState* play) {
  if (actor->init != NULL) {
    actor->init(actor, play);
    actor->init = NULL;
  }
}

void Actor_UpdateAll(ActorContext* actorCtx, PlayState* play) {
  Actor* actor = actorCtx->actorHead;

  while (actor != NULL) {
    actor->update(actor, play);
    // TODO: for now drawing happens here
    actor->draw(actor, play);
    actor = actor->next;
  }
}
