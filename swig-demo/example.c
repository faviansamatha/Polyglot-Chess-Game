#include "example.h"

int escapes(double cr, double ci, int it) {
  double zr = 0;
  double zi = 0;
  double zrtmp;
  int i;
  
  for(i=0; i<it; i++) {
    // z <- z^2 + c
    zrtmp = zr*zr - zi*zi + cr;
    zi = 2*zr*zi + ci;
    zr = zrtmp;
    if (zr*zr + zi*zi > 4) {
      return 1;
    }
  }
  return 0;
}

int fact(int n) {
    if (n <= 1) return 1;
    else return n*fact(n-1);
}
