#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "color.h"
#include "func.h"
#include <memory>

class Fill {
private:
  double opacity = 0;
  Color color = Color();
  std::vector<Function*> funcs = std::vector<Function*>();
  int fill_type = 0;// 1 for above, 2 for below, 3 for between

public:
  Fill();
  Fill(int opacity, Color color, std::vector<std::unique_ptr<Function>> funcs, int fill_type);
  ~Fill();

  //Getter and setter methods 
  double get_opacity() const;
  int get_type() const;
  Color get_color() const;
  const Function& get_func(int i) const;//returns Function in funcs at index i
  
  void set_opacity(double opacity);
  void set_color(Color color);
  void set_type(int type);

  void add_function(Function* f);//appends a new function at the end of the funcs vector

};

#endif // FILL_H
