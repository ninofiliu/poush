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

// PARAMS

float min_vel = 20;
float max_vel = 150;
float min_light = 0.3;
float max_light = 0.9;
float min_hour = 9;
float max_hour = 24;

// GLOBALS

float h = 0;
float dir_stable = 0;
float vel_stable = 0;
RTC_DS1307 rtc;

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
  float hue = fmod(dir_stable+0.1, 1);

  float vel = (float)analogRead(A1);
  vel_stable = 0.95 * vel_stable + 0.05 * vel;
  float light;
  if (vel_stable < min_vel) { light = min_light; }
  else if (vel_stable > max_vel) { light = max_light; }
  else { light = min_light + (vel_stable-min_vel) * (max_light-min_light) / (max_vel-min_vel); }
  
  write_rgbw(hue, light);
  Serial.print(100*hue);
  Serial.print(",");
  Serial.print(100*light);
  Serial.println();
  delay(50);
}
