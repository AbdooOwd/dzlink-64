#ifndef DZ_OBJ_N64_LOGO_H
#define DZ_OBJ_N64_LOGO_H

#include "rdpq.h"
#include "t3d/t3dmath.h"
#include <dz_actor.h>

#define N64_MODEL_FILENAME  "rom:/n64.t3dm"

struct ObjN64Logo;

typedef void (*ObjN64LogoActionFunc)(struct ObjN64Logo*);

typedef struct ObjN64Logo {
  Actor actor;
  ObjN64LogoActionFunc actionFunc;
  T3DMat4FP* mat4fp;
  rspq_block_t* dplDraw;
} ObjN64Logo;

#endif
