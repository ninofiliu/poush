#include "moving-average.h"

void MovingAverage::init() {
  for (int i = 0; i < SIZE; i++) {
    values[i] = 0;
  }
};
void MovingAverage::add(float value) {
  values[index] = value;
  index = (index + 1) % SIZE;
};
float MovingAverage::get() {
  float sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += values[i];
  }
  return sum / SIZE;
}
