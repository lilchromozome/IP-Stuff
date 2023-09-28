#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  const Plot &m_plot = Plot();
  Image *m_img = NULL;

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

public:
  Renderer(const Plot &plot);
  ~Renderer();

  Image *render();
  void render_fills(int &width, int &height, Bounds &bounds, Image *m_img, std::vector<double> opacitys);//renders the fills
  void render_lines(int &width, int &height, Bounds &bounds, Image *m_img);//renders the lines


};

#endif // RENDERER_H
