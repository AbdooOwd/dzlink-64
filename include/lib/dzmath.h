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


#define VEC3_ZERO (Vec3){{0, 0, 0}}
#define VEC3(x, y, z) (Vec3){{x, y, z}}


#define BINANG_PER_DEG  182.0444444444444444f
#define BINANG_PER_RAD  10430.3783504704527246f
#define RAD_PER_DEG     0.0174532925199432f

// TRUNCF_BINANG stolen from ZeldaOoT (:<
#define TRUNCF_BINANG(f)  (binang)(s32)(f)

#define DEG_TO_RAD(deg) ((deg) * RAD_PER_DEG)
#define DEG_TO_BINANG(deg) TRUNCF_BINANG((deg) * BINANG_PER_DEG)
#define RAD_TO_DEG(rad) ((rad) / RAD_PER_DEG)
#define RAD_TO_BINANG(rad)  TRUNCF_BINANG((rad) * BINANG_PER_RAD)
#define BINANG_TO_DEG(binangle) ((binangle) / BINANG_PER_DEG)
#define BINANG_TO_RAD(binangle) ((binangle) / BINANG_PER_RAD)


float dz_cos(binang angle);
float dz_sin(binang angle);
float dz_tan(binang angle);

#endif
