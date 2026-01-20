#ifndef DZ_MATH_H
#define DZ_MATH_H

#include <lib/types.h>

#define PI          3.14159265358979323846f
#define PI_SQUARED  9.86960440108935861881f
#define PI_HALF     1.57079632679489661923f
#define PI_INV      0.31830988618379067153f

#define Q15_PI      0x8000  // half a circle (32768 in binang. pi in rads. 180°)
#define Q15_PI_SQR  0x40000000
#define Q15_PI_HALF 0x4000

float dz_cos(s16 angle);
float dz_sin(s16 angle);

#endif
