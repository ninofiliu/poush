#include <Wire.h>
#include "RTClib.h"
#include <DmxSimple.h>

// UTILS

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

void write_rgbw(float h, float l) {
  float r = 0;
  float g = 0;
  float b = 0;
  float w = 0;

  if (h<0.25) {
    r = 4*h;
    w = 1-4*h;
  } else if (h<0.5) {
    g = 4*(h-0.25);
    r = 4*(0.5-h);
  } else if(h<0.75) {
    b = 4*(h-0.5);
    g = 4*(0.75-h);
  } else {
    w = 4*(h-0.75);
    b = 4*(1-h);
  }

  r = w>r ? w : r;
  g = w>g ? w : g;
  b = w>b ? w : b;

  write_rgb(
    (int)(255. * r * l),
    (int)(255. * g * l),
    (int)(255. * b * l)
  );
}

void interpolate(float dst[], float c, float from[], float to[]) {
  for (int i = 0; i < 3; i++) {
    dst[i] = (1.0 - c) * from[i] + c * to[i];
  }
};

void interpolate_many(float *dst, float c, float *colors) {
  int index = (int)c;
  float sub_cursor = c - (float)index;
  float from[3];
  float to[3];
  for (int i = 0; i < 3; i++) {
    from[i] = colors[3 * index + i];
    to[i] = colors[3 * (index + 1) + i];
  }
  interpolate(dst, sub_cursor, from, to);
}

// PARAMS

float min_vel = 80; // anemometer value (A1) when the wind is low
float max_vel = 160; // anemometer value (A1) when the wind is high
float min_light = 0.3; // luminosity when the wind is low, in the range 0 - max_light
float max_light = 0.9; // luminosity when the wind is high, in the range min_light - 1
float min_hour = 9; // when to turn on
float max_hour = 24; // when to turn off
float nb_colors = 5; // number of colors
float colors[18] = { // = 3 x (nb_colors + 1)
  0.9,  0.9,  0.9, // white
  1.0,  0.5,  0.0, // orange
  1.0,  0.3,  0.0, // yellow
  1.0,  0.2,  0.2, // pink
  0.1,  0.1,  1.0, // blue
  0.9,  0.9,  0.9, // white again (for clean looping)
};
float hue_offset = 0.1; // desired hue - dir_stable when the wind direction is stable

// GLOBALS

float h = 0;
float dir_stable = 0;
float vel_stable = 0;
float color[3] = {0,0,0};
RTC_DS1307 rtc;
float dir_debug = 0;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  if (now.hour() < min_hour || now.hour() > max_hour) {
    write_rgb(0,0,0);
    delay(10000);
    return;
  }

  float dir = ((float)analogRead(A0))/1000;
  dir_stable = 0.9 * dir_stable + 0.1 * dir;
  float hue = fmod(dir_stable+hue_offset, 1);

  interpolate_many(color, nb_colors * hue, colors);

  float vel = (float)analogRead(A1);
  vel_stable = 0.95 * vel_stable + 0.05 * vel;
  float light;
  if (vel_stable < min_vel) { light = min_light; }
  else if (vel_stable > max_vel) { light = max_light; }
  else { light = min_light + (vel_stable-min_vel) * (max_light-min_light) / (max_vel-min_vel); }

  write_rgb(
    (int)(255*light*color[0]),
    (int)(255*light*color[1]),
    (int)(255*light*color[2])
  );

  delay(50);
}
