 #ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cassert>
#include <cmath>
#include <type_traits>
struct Color {
public:
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  //constructor
  Color(): r('\0'), g('\0'), b('\0'){}
  Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
  
  bool operator !=(const Color &rhs){
    if(this->r == rhs.r){
      if(this->g == rhs.g){
        if(this->b == rhs.b){return false;}
      }
    }
    return true;
  }

  // member functions for doing operations on Color values

  Color setOpacity(double opacity) {//returns color with opacity value
    Color c;
    c.r = r * opacity;
    c.g = g * opacity;
    c.b = b * opacity; 
    return c;
  }

  Color blend(double opacity, Color old_color){//returns the blend of current color and inputted color with an opacity value
    Color c;
    c.r = std::floor((1 - opacity) * old_color.r + (opacity * r));
    c.g = std::floor((1 - opacity) * old_color.g + (opacity * g));
    c.b = std::floor((1 - opacity) * old_color.b + (opacity * b));
    return c;
  }

};

#endif // COLOR_H
