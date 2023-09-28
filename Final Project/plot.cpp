#include <cassert>
#include "exception.h"
#include "plot.h"
#include <sstream>
#include <memory>
Plot::Plot(){}

Plot::~Plot()
{
  for(size_t i = 0; i < funcs.size(); i++){
    delete funcs.at(i);
  }
}

// implementations of Plot member functions
Bounds Plot::get_bounds() const{
  return bounds;
}

int Plot::get_width() const{
  return x_dim;
}

int Plot::get_height() const{
  return y_dim;
}

const Function& Plot::get_func(int i) const {
  return *funcs.at(i);
}

const Fill& Plot::get_fill(int i) const{
  return fills.at(i);
}

Color Plot::get_color(int i) const{
  return colors.at(i);
}

bool Plot::get_color_init(int i) const{
  return colors_init.at(i);
}

int Plot::get_num_funcs() const{
  return funcs.size();
}
int Plot::get_num_fills() const{
  return fills.size();
}
int Plot::get_num_colors() const{
  return colors.size();
}

void Plot::set_bounds(double xmin, double xmax, double ymin, double ymax){
  bounds.set_bounds(xmin, xmax, ymin, ymax);
}

void Plot::set_dimensions(int x_dim, int y_dim){
  this->x_dim = x_dim;
  this->y_dim = y_dim;
}

void Plot::add_function(const std::string &name, Expr *expr) {
  Function* func1(new Function(name, expr));
  funcs.push_back(std::move(func1));
}

void Plot::add_color(const Color color, int pos){
  colors.at(pos) = color;
}

void Plot::set_color_init(int pos){
  colors_init.at(pos) = true;
}

void Plot::add_fill(const Fill fill){
  fills.push_back(fill);
}

//Helper functions for parallel func and color array 
Function& Plot::get_func(std::string name) {
  for (size_t i = 0; i < funcs.size(); i++){
    if (funcs.at(i)->get_name() == name){
      return *funcs.at(i);
    }
  }
  //if not found
  std::stringstream sserr;
  sserr << name << " not found";
  throw PlotException(sserr.str());
}

int Plot::get_func_pos(std::string name) {
  for (size_t i = 0; i < funcs.size(); i++){
    if (funcs.at(i)->get_name() == name){
      return i;
    }
  }
  //if not found
  std::stringstream sserr;
  sserr << name << " not found";
  throw PlotException(sserr.str());
}

void Plot::resize_color(int size){
  colors.resize(size);
}

void Plot::resize_color_init(int size){
  colors_init.resize(size);
}