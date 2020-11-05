#include <DmxSimple.h>
#include "./utils/colors.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  float dir = ((float)analogRead(A0))/1000.0;
  write_h(dir);
  delay(10);
}
