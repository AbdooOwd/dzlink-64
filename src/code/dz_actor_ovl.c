/*
 * This file controls how actors are used and recognized across
 * the game & source code (i think)
*/

#include "dz_actor_ovl.h"
#include <dz_actor.h>

/*
 * For each actor defined entry, we declare its profile as external
 * to be usable by the actors' overlay table
 * */

#define DEFINE_ACTOR(name, _1, _2) extern ActorProfile name##_Profile;
#include <tables/actor_table.h>
#undef DEFINE_ACTOR

#define DEFINE_ACTOR(name, _1, _2)  \
  {                                 \
    &name##_Profile,                \
    0                               \
  },

ActorOverlay gActorOverlayTable[] = {
#include <tables/actor_table.h>
};

#undef DEFINE_ACTOR
