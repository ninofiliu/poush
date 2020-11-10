#include <stdio.h>

void interpolate(float dst[], float cursor, float from[], float to[]) {
  for (int i = 0; i < 3; i++) {
    dst[i] = (1.0 - cursor) * from[i] + cursor * to[i];
  }
};

void interpolate_2(float dst[], float cursor, float c0[], float c1[], float c2[]) {
  if (cursor<0.5) {
    interpolate(dst, (cursor-0.0)*2.0, c0, c1);
  } else {
    interpolate(dst, (cursor-0.5)*2.0, c1, c2);
  }
}

void interpolate_many(float *dst, float cursor, float *colors) {
  int index = (int)cursor;
  float sub_cursor = cursor - (float)index;
  float from[3];
  float to[3];
  for (int i = 0; i < 3; i++) {
    from[i] = colors[3 * index + i];
    to[i] = colors[3 * (index + 1) + i];
  }
  interpolate(dst, sub_cursor, from, to);
}

//

int main() {
  float dst[3] = {0,0,0};
  float colors[12] = {
    1,0,0,
    0,1,0,
    0,0,1,
    1,1,1
  };
  for (float cursor = 0; cursor < 3; cursor += 0.1) {
    interpolate_many(dst, cursor, colors);
    printf("%f : %f %f %f\n", cursor, dst[0], dst[1], dst[2]);
  }
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
