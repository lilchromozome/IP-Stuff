#include "bounds.h"
#include <cstddef>

Bounds::Bounds() {
}

//getter and setter methods for bounds
double Bounds::get_xmin() const{
    return xmin;
}

double Bounds::get_xmax() const{
    return xmax;
}

double Bounds::get_ymin() const{
    return ymin;
}

double Bounds::get_ymax() const{
    return ymax;
}

double Bounds::get_xval(int row, int width){
    double xcoord = xmin + (row/width) * (xmax - xmin);
    return xcoord;
}

double Bounds::get_yval(int col, int height){
    double ycoord = ymin + ((height - 1 - col)/height) * (ymax - ymin);
    return ycoord;
}

void Bounds::set_bounds(double xmin, double xmax, double ymin, double ymax){
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
}
