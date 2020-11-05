#include "./utils/colors.h"

float h = 0.;

void setup() {
}

void loop () {
  write_hl(h, 1.);
  h = fmod(h+0.01, 1);
  delay(50);
}
