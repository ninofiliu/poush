#include <iostream>

# define SIZE 10

class MovingAverage {
  private:
    int index;
    float values[SIZE];
  public:
    void init() {
      for (int i = 0; i < SIZE; i++) {
        values[i] = 0;
      }
    }
    void add(float value) {
      values[index] = value;
      index = (index + 1) % SIZE;
    };
    float get() {
      float sum = 0;
      for (int i = 0; i < SIZE; i++) {
        sum += values[i];
      }
      return sum / SIZE;
    };
};

int main() {
  MovingAverage ma;
  ma.init();
  printf("%f\n", ma.get());
  ma.add(10);
  printf("%f\n", ma.get());
  ma.add(20);
  printf("%f\n", ma.get());
  return 0;
}
