#include <iostream>
#include <vector>

class Color {
private:
  int r, g, b;

public:
    Color(): r(0), g(0), b(0) {}
  Color(int r_, int g_, int b_)
    : r(r_), g(g_), b(b_)
  { }

  int get_r() const { return r; }
  int get_g() const { return g; }
  int get_b() const { return b; }

  void set_r(int r_) { r = r_; }
  void set_g(int g_) { g = g_; }
  void set_b(int b_) { b = b_; }
};

int main() {
    Color palette[10];
  // create a grayscale palette
  for (int i = 0; i < 10; i++) {
    int intensity = (int) (((float)i / 10) * 255);
    palette[i].set_r(intensity);
    palette[i].set_g(intensity);
    palette[i].set_b(intensity);
  }
}

/*
In the line Coloor palette[10] you try to initialize an array of Color objects, and this will call the default parameter for each of the instances. However, there is no default constructor for the Color class. We can fix this by either creating a default constructor Color or we cann use a vector instead of an array.
For example: under public:
Color(): r(0), g(0), b(0) {}
*/