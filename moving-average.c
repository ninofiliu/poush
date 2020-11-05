#include <stdio.h>

# define SIZE 10

int index = 0;
float values[SIZE];

void setup() {
  for (int i = 0; i < SIZE; i++) {
    values[i] = 0.;
  }
}

void add(float value) {
  values[index] = value;
  index = (index + 1) % SIZE;
}

float get() {
  float sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += values[i];
  }
  return sum / SIZE;
}

int main() {
  setup();
  printf("%f\n", get());
  add(10.);
  add(10.);
  printf("%f\n", get());
  return 0;
}
