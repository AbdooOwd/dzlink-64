#include <lib/dzmath.h>

/*
 *  By the Indian mathematician Bhaskara I
 *  in the 7th century who came up with an approximate
 *  formula for cos:
 *
 *  cos(x) ~= (pi^2 - 4(x^2)) / (pi^2 + x^2)
 *
 *  @param takes an angle in BINANGS
 * */
float dz_cos(binang angle) {
  bool flipsign = ((angle ^ (angle << 1)) & 0x8000) != 0;
  if (flipsign)
      angle = 0x8000 - angle;

  s32 xx = angle * angle;
  s64 xx4 = xx << 2; // times 4
  float cosine = (Q15_PI_SQR - (float) xx4) / (Q15_PI_SQR + (float) xx); // THIS COSTS 29-58 CYCLES NOOOO

  return flipsign ? -cosine : cosine;
}

float dz_sin(binang angle) {
  return dz_cos(angle - Q15_PI_HALF);
}
