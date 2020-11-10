#include <stdio.h>

void interpolate(float dst[], float cursor, float from[], float to[]) {
  for (int i = 0; i < 3; i++) {
    dst[i] = (1 - cursor) * from[i] + cursor * to[i];
  }
};

void interpolate_2(float dst[], float cursor, float c0[], float c1[], float c2[]) {
  if (cursor<0.5) {
    interpolate(dst, (cursor-0.0)*2.0, c0, c1);
  } else {
    interpolate(dst, (cursor-0.5)*2.0, c1, c2);
  }
}

//

int main() {
  return 0;
}

//

void interpolate_example() {
  float red[3] = {1,0,0};
  float green[3] = {0,1,0};
  float brown[3];
  interpolate(brown, 0.4, red, green);
  printf("%f %f %f\n", brown[0], brown[1], brown[2]);
}

void interpolate_2_example() {
  float dst[3];
  float c0[3] = {1,0,0};
  float c1[3] = {0,1,0};
  float c2[3] = {0,0,1};
  for (float cursor = 0.0; cursor < 1; cursor += 0.1) {
    interpolate_2(dst, cursor, c0, c1, c2);
    printf("%f : %f %f %f\n", cursor, dst[0], dst[1], dst[2]);
  }
}
