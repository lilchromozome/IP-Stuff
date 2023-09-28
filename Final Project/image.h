#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height = 0;
  Color *m_pixels = NULL;

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  Image(int width, int height);
  ~Image();

  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  //Member function to access pixel Color data
  
  //Getter and setter methods for pixels
  Color get_color(int x_pos, int y_pos) const;
  void set_color(int x_pos, int y_pos, Color c);
  
  void write_png(std::ostream &out);
};

#endif // IMAGE_H
