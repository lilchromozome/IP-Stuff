#include <cassert>
#include "fill.h"
//default constructor
Fill::Fill() {
}
//constructor
Fill::Fill(int opacity, Color color, std::vector<std::unique_ptr<Function>>funcs, int fill_type){
    this->opacity = opacity;
    this->color = color;
    this->fill_type = fill_type;
    for(size_t i = 0; i < funcs.size(); i++){
        Function* func1(new Function(funcs[i]->get_name(), funcs[i]->get_expr()));
        this->funcs.push_back(std::move(func1));
    }
}

Fill::~Fill() {
}


//Getter and Setter methods
double Fill::get_opacity() const{
    return opacity;
}

int Fill::get_type() const {
    return fill_type;
}

Color Fill::get_color() const {
    return color;
}

const Function& Fill::get_func(int i) const{
    return *funcs.at(i);
}

void Fill::set_opacity(double opacity){
    this->opacity = opacity;
}

void Fill::set_color(Color color){
    this->color = color;
}

void Fill::set_type(int type){
    this->fill_type = type;
}

void Fill::add_function(Function* f) {
    funcs.push_back(std::move(f));
}



