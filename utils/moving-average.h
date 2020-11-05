# define SIZE 10

class MovingAverage {
  private:
    int index;
    float values[SIZE];
  public:
    void init();
    void add(float value);
    float get();
};
