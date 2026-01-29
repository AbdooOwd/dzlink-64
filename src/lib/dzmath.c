#include "t3d/t3dmath.h"
#include <lib/dzmath.h>
#include <math.h>

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
      angle = Q15_PI - angle;

  s32 xx = angle * angle;
  s64 xx4 = xx << 2; // times 4
  float cosine = (Q15_PI_SQR - (float) xx4) / (Q15_PI_SQR + (float) xx); // THIS COSTS 29-58 CYCLES NOOOO

  return flipsign ? -cosine : cosine;
}

float dz_sin(binang angle) {
  return dz_cos(angle - Q15_PI_HALF);
}

float dz_tan(binang angle) {
  float c = cos(angle);
  if (c <= 0.0000000000000001f)
    c = 0.0000000000000001f;

  float tan = (dz_sin(angle)) / c;

  return tan;
}

void dz_mat4_from_srt_euler(T3DMat4 *mat, const float scale[3], const binang rot[3], const float translate[3]) {
  float cosR0 = dz_cos(rot[0]);
  float cosR2 = dz_cos(rot[2]);
  float cosR1 = dz_cos(rot[1]);

  float sinR0 = dz_sin(rot[0]);
  float sinR1 = dz_sin(rot[1]);
  float sinR2 = dz_sin(rot[2]);

  *mat = (T3DMat4){{
    {scale[0] * cosR2 * cosR1, scale[0] * (cosR2 * sinR1 * sinR0 - sinR2 * cosR0), scale[0] * (cosR2 * sinR1 * cosR0 + sinR2 * sinR0), 0.0f},
    {scale[1] * sinR2 * cosR1, scale[1] * (sinR2 * sinR1 * sinR0 + cosR2 * cosR0), scale[1] * (sinR2 * sinR1 * cosR0 - cosR2 * sinR0), 0.0f},
    {-scale[2] * sinR1, scale[2] * cosR1 * sinR0, scale[2] * cosR1 * cosR0, 0.0f},
    {translate[0], translate[1], translate[2], 1.0f}
  }};
}

void dz_mat4fp_from_srt_euler(T3DMat4FP* mat, const float scale[3], const binang rot[3], const float translate[3]) {
  T3DMat4 mat4;
  dz_mat4_from_srt_euler(&mat4, scale, rot, translate);
  t3d_mat4_to_fixed_3x4(mat, &mat4);
}
