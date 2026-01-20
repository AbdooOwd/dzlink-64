#ifndef ACTOR_H
#define ACTOR_H

#include <t3d/t3dmath.h>
#include <lib/types.h>

struct Actor;
struct ActorOverlay;

typedef void (*ActorFunc)(struct Actor*);

typedef struct Actor {
  u16 id; // Actor's type, techincally. usually a value of ActorID enum
  PosRot home; // posrot when actor was spawned
  PosRot world; // current posrot in the world
  u16 params;

  struct Actor* prev;
  struct Actor* next;
  struct ActorOverlay* overlayEntry; // local pointer to actor's overlay entry
  ActorFunc init;
  ActorFunc update;
  ActorFunc draw;
  ActorFunc destroy;
} Actor;

/*
 * Consider this an "info source" for any instance of an actor
 * */
typedef struct ActorProfile {
  u16 id;
  u32 instance_size;
  ActorFunc init;
  ActorFunc update;
  ActorFunc draw;
  ActorFunc destroy;
} ActorProfile;

typedef struct ActorContext {
  u16 total; // total number of actors loaded
  Actor* actorHead; // latest actor. access its `prev` to loop back the "actors' chain"
} ActorContext;

#define DEFINE_ACTOR(_0, _1, actor_enum_value) actor_enum_value,

typedef enum ActorID {
  ACTOR_ID_NONE,
  #include <tables/actor_table.h>
  ACTOR_ID_MAX
} ActorID;

#undef DEFINE_ACTOR


void Actor_Init(Actor* actor);
void ActorContext_Destroy(ActorContext* actorCtx);
Actor* Actor_Spawn(ActorContext* actorCtx, ActorID actor_id, float pos[3], float rot[3]);
ActorContext* ActorContext_Init();
void Actor_UpdateAll(ActorContext* actorCtx);

#endif
