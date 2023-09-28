#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {

}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();
  Bounds bounds = m_plot.get_bounds();
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();
  std::vector<double> opacitys(width * height, -1);
  
  //render fill
  render_fills(width, height, bounds, m_img, opacitys);
  
  //render lines
  render_lines(width,height,bounds,m_img);
  
  return img.release();
}

void Renderer::render_fills(int &width, int &height, Bounds &bounds, Image *m_img, std::vector<double> opacitys){
  try{
    for(int c = 0; c < m_plot.get_num_fills();c++){
      const Fill* current = &(m_plot.get_fill(c));
      double current_opacity = current->get_opacity();
      const Function& f1 = current->get_func(0);
      Color current_color = current->get_color();
      Color non_blended = current_color.setOpacity(current_opacity);
    
      for(int a = 0; a < width; a++){
          double x_val = bounds.get_xmin()+(a/(double)width)*(bounds.get_xmax()-bounds.get_xmin());
          double y_val_1 = f1.eval(x_val);
          
          if(y_val_1 > bounds.get_ymax()){
            y_val_1 = bounds.get_ymax();
          }
          if(y_val_1 < bounds.get_ymin()){
            y_val_1 = bounds.get_ymin();
          }
          
          int y_pos_1 = (double)height - 1 - std::floor((y_val_1 - bounds.get_ymin()) / (bounds.get_ymax() - bounds.get_ymin()) * (double)height);
          
          if(current->get_type() == 1){
            for(int b = y_pos_1;b>=0;b--){
              if(opacitys.at(a*height+b) != -1){
                Color blended = current_color.blend(current_opacity,m_img->get_color(a,b));
                m_img->set_color(a,b,blended);
              }
              else{
                opacitys.at(a*height+b) = current_opacity;
                m_img->set_color(a,b,non_blended);
              }
              
            }
          }

          else if(current->get_type() == 2){
            for(int b = y_pos_1+1;b<height;b++){
              if(opacitys.at(a*height+b) != -1){
                Color blended = current_color.blend(current_opacity,m_img->get_color(a,b));
                m_img->set_color(a,b,blended);
              }
              else{
                opacitys.at(a*height+b) = current_opacity;
                m_img->set_color(a,b,non_blended);
              }
            }
          }

          else if(current->get_type() == 3){
            const Function& f2 = current->get_func(1);
            double y_val_2 = f2.eval(x_val);
            
            if(y_val_2 > bounds.get_ymax()){
              y_val_2 = bounds.get_ymax();
            }
            if(y_val_2 < bounds.get_ymin()){
              y_val_2 = bounds.get_ymin();
            }
            int y_pos_2 = (double)height - 1 - std::floor((y_val_2 - bounds.get_ymin()) / (bounds.get_ymax() - bounds.get_ymin()) * (double)height);
            
            for(int b = y_pos_1+1;b<y_pos_2;b++){
              if(opacitys.at(a*height+b) != -1){
                Color blended = current_color.blend(current_opacity,m_img->get_color(a,b));
                m_img->set_color(a,b,blended);
              }
              
              else{
                opacitys.at(a*height+b) = current_opacity;
                m_img->set_color(a,b,non_blended);
              }
            }

            for(int b = y_pos_2+1;b<y_pos_1;b++){
              if(opacitys.at(a*height+b) != -1){
                Color blended = current_color.blend(current_opacity,m_img->get_color(a,b));
                m_img->set_color(a,b,blended);
              }

              else{
                opacitys.at(a*height+b) = current_opacity;
                m_img->set_color(a,b,non_blended);
              }
            }
          } 
        
      }
    
    }
  
  }
  
  catch(PlotException& e){
    std::cerr << "Error: " << e.what() << std::endl;
    exit(1);
  }
}

void Renderer::render_lines(int &width, int &height, Bounds &bounds, Image *m_img){
  //interate through the functions
  for(int i = 0; i< m_plot.get_num_funcs();i++){
    Color c;
    
    if(m_plot.get_num_colors()==0 ||!m_plot.get_color_init(i)){
      c.r = 255;
      c.b = 255;
      c.g = 255;
    }
    else {
      c = m_plot.get_color(i);
    }

    const Function& f = m_plot.get_func(i);
    //interate through the pixels
    for (int j = 0; j < width; j++) {
      //get pixel y coordinate
      //For a pixel column j, the pixel row i is computed as i=h−1−⌊((y−ymin)/(ymax−ymin))×h⌋
      //where y=f(xmin+(j/w)×(xmax−xmin))
      double x_val = bounds.get_xmin()+(j/(double)width)*(bounds.get_xmax()-bounds.get_xmin());
      double y_val = f.eval(x_val);
      if(y_val > bounds.get_ymax() || y_val < bounds.get_ymin()){
        continue;
      }
      int y_pos = (double)height - 1 - std::floor((y_val - bounds.get_ymin()) / (bounds.get_ymax() - bounds.get_ymin()) * (double)height);
      //std::cout << "y_val: " << y_val << " y_pos: " << y_pos << std::endl;
      //set the calculated pixel
      m_img->set_color(j, y_pos,c);
      //set the surrounding pixels
      if(y_pos+1 < height){
        m_img->set_color(j, y_pos+1,c);
      }
      if(y_pos-1 >= 0){
        m_img->set_color(j, y_pos-1,c);
      }
      if(j+1 < width){
        m_img->set_color(j+1, y_pos,c);
      }
      if(j-1 >= 0){
        m_img->set_color(j-1, y_pos,c);
      }
    
    }
  
  }
}