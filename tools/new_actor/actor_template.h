#ifndef DZ_{{ActorFilenameUPPER}}_H
#define DZ_{{ActorFilenameUPPER}}_H

#include <rdpq.h>
#include <dz_actor.h>

struct {{ActorName}};

typedef void (*{{ActorName}}ActionFunc)(struct {{ActorName}}*);

typedef struct {{ActorName}} {
  Actor actor;
  {{ActorName}}ActionFunc actionFunc;
  T3DMat4FP* mat4fp;
  rspq_block_t* dplDraw;
} {{ActorName}};

#endif
