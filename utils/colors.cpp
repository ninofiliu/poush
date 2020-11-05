#include <DmxSimple.h>

void write_rgb(int r, int g, int b) {
  DmxSimple.write(1, r);
  DmxSimple.write(2, g);
  DmxSimple.write(3, b);
}

void write_hl(float h, float l) {
  float r = 0;
  float g = 0;
  float b = 0;
  if (h < 1. / 3.) {
    r = 1. - 3. * h;
    g = 3. * h;
  }
  if (h >= 1. / 3. && h < 2. / 3.) {
    g = 2. - 3. * h;
    b = -1. + 3. * h;
  }
  if (h >= 2. / 3.) {
    b = 3. - 3. * h;
    r = -2. + 3. * h;
  }
  write_rgb(
    (int)(255. * r * l),
    (int)(255. * g * l),
    (int)(255. * b * l)
  );
}
