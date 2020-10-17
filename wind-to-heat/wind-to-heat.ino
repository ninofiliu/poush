#include<DmxSimple.h>

float get_wind() {
  float min_wind = 80;
  float max_wind = 130;
  float real_wind = (float)analogRead(A0);
  if (real_wind < min_wind) return 0;
  if (real_wind > max_wind) return 1;
  return (real_wind - min_wind) / (max_wind - min_wind);
}

void write_wind(float wind) {
  int red = (int)(255.*wind);
  int blue = (int)(255.*(1.-wind));
  DmxSimple.write(1, red);
  DmxSimple.write(2, 0);
  DmxSimple.write(3, blue);  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float wind = get_wind();
  write_wind(wind);
  Serial.println(1000*wind);
  delay(10);
}
