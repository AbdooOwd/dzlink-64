#ifndef TYPES_H
#define TYPES_H

#include "t3d/t3dmath.h"
#include <stdint.h>

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef T3DVec3 Vec3;

typedef struct PosRot {
  Vec3 pos;
  Vec3 rot;
} PosRot;

#endif
