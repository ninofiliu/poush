int min_dir;
int max_dir;

void setup() {
  Serial.begin(9600);
  min_dir = analogRead(A0)-1;
  max_dir = analogRead(A0)+1;
}

void loop() {
  int dir = analogRead(A0);
  if (dir < min_dir) {
    min_dir = dir;
  }
  if (dir > max_dir) {
    max_dir = dir;
  }
  float dir = (float)(dir - min_dir) / (float)(max_dir - min_dir);

  Serial.println(100.0 * dir);

  delay(10);
}
