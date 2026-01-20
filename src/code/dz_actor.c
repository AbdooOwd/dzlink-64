#include "dz_actor_ovl.h"
#include "n64sys.h"
#include <dz_actor.h>
#include <lib/utils.h>

void Actor_Init(Actor* actor) {
  if (actor->init != NULL) {
    actor->init(actor);
    actor->init = NULL;
  }
}

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

Actor* Actor_Spawn(ActorContext* actorCtx, ActorID actor_id, float pos[3], float rot[3]) {
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

  Actor_Init(newActor);

  return newActor;
}

void Actor_UpdateAll(ActorContext* actorCtx) {
  Actor* actor = actorCtx->actorHead;

  while (actor != NULL) {
    actor->update(actor);
    // TODO: for now drawing happens here
    actor->draw(actor);
    actor = actor->next;
  }
}
