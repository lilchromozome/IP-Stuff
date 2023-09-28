#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"
#include <memory>

class Plot {
private:
  //Fields to represent plot bounds, functions, fills, colors and image size
  Bounds bounds = Bounds();
  std::vector<Function*> funcs = std::vector<Function*>();
  std::vector<Color> colors = std::vector<Color>();
  std::vector<bool> colors_init = std::vector<bool>(0,false);
  std::vector<Fill> fills = std::vector<Fill>();
  double x_dim = 0;
  double y_dim = 0;
  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);


public:
  Plot();
  ~Plot();

  //Getter and setter methods
  Bounds get_bounds() const;
  int get_width() const;
  int get_height() const;
  void set_bounds(double xmin, double xmax, double ymin, double ymax);
  void set_dimensions(int x_dim, int y_dim);
  
  int get_num_funcs() const;//returns number of Functions in the funcs vector
  int get_num_fills() const;//returns number of Functions in the fills vector
  int get_num_colors() const;//returns number of Colorss in the fills vector
  const Function& get_func (int i) const;//returns Function in funcs at index i
  const Fill& get_fill (int i) const;//returns Fill in fills at index i
  Color get_color(int i) const;//returns Color in colors at index i
  bool get_color_init(int i) const;//returns boolean value for initializaiton status for index i
  
  void add_function(const std::string &name, Expr *expr);//appends a new function at the end of the funcs vector
  void add_color(const Color color,int pos);//appends a new color at the specified location
  void add_fill(const Fill fill);//appends a new fill at the end of the fill vector
  void set_color_init(int pos);//appends a new boolean value at the specified location

  //Helper methods for the parallel funcs and colors vectors
  Function& get_func(std::string name);//returns the function that matches the input in the funcs vector
  int get_func_pos(std::string name);//returns the position of the function that matches the input in the funcs vector
  void resize_color(int size);// resizes the color  (used to match the length of the function)
  void resize_color_init(int size);// resizes the color_init  (used to match the length of the function)
};

#endif // PLOT_H
