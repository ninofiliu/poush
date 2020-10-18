void print_arr(int arr[], int l) {
  for (int i = 0; i < l; i++) {
    Serial.print(arr[i]);
    if (i < l - 1) {
      Serial.print(",");
    }
  }
  Serial.println("");
}

int min_observed;
int max_observed;

void setup() {
  min_observed = 1023;
  max_observed = 0;
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  if (v < min_observed) {
    min_observed = v;
  }
  if (v > max_observed) {
    max_observed = v;
  }
  int to_print[3] = {min_observed, max_observed, v};
  print_arr(to_print, 3);
  delay(10);
}
