#include "pnglite.h"
#include "exception.h"
#include "image.h"
namespace {

struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite;

unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height): m_width(width), m_height(height), m_pixels(new Color[width * height]) {
}

//deallocate memory
Image::~Image() {
  delete [] m_pixels;
}

//Member functions

//Getter method for pixel
Color Image::get_color(int x_pos, int y_pos) const{
  return m_pixels[x_pos+y_pos*m_width];
}

//Setter method for pixel
void Image::set_color(int x_pos, int y_pos, Color c){
  m_pixels[x_pos+y_pos*m_width].r = c.r;
  m_pixels[x_pos+y_pos*m_width].g = c.g;
  m_pixels[x_pos+y_pos*m_width].b = c.b;
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(m_pixels);
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error converting writing image data as PNG");
  }
}
