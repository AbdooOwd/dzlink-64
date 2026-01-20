float dz_cos(binang angle) {
  bool flipsign = ((angle ^ (angle << 1)) & 0x8000) != 0;
  if (flipsign)
      angle = 0x8000 - angle;

  float xx = (float) angle * (float) angle;
  float xx4 = xx + xx + xx + xx; // thx kaze
  float cosine = (Q15_PI_SQR - xx4) / (Q15_PI_SQR + xx);

  return flipsign ? -cosine : cosine;
}
