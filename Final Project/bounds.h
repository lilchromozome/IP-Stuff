#ifndef BOUNDS_H
#define BOUNDS_H
/*
  
*/
class Bounds {
private:
  //instance variables
  double xmin = 0;
  double xmax = 0;
  double ymin = 0;
  double ymax = 0;
  
public:
  //constructors
  Bounds();
  Bounds(const double & xmin, const double & xmax, double & ymin, const double & ymax): xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {};

  //getter and setter methods for bounds
  double get_xmin() const;
  double get_xmax() const;
  double get_ymin() const;
  double get_ymax() const;
  double get_xval(int row, int width);
  double get_yval(int col, int height);
  void set_bounds(double xmin, double xmax, double ymin, double ymax);
};

#endif // BOUNDS_H
