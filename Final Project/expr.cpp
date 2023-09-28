#include <cctype>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#include <vector>
#include "exception.h"
#include "expr.h"


// Expr (base class)
Expr::Expr(Expr* left, Expr* right, double val) {
  set_left(left);
  set_right(right);
  set_val(val);
}

void Expr::deleteRecursive(Expr*& node){
  if(node){
    deleteRecursive(node->left);
    deleteRecursive(node->right);
    delete node;
    node = nullptr;
  }
}
// destructor
Expr::~Expr() {
  deleteRecursive(left);
  deleteRecursive(right);
}

bool Expr::isNumeric(std::string token){
  bool dec = false;
  for (size_t i = 0; i < token.length(); i++){
    if(!isdigit(token[i])){
      if(token[i] == '.' && !dec){
        dec = true;
        continue;
      }
      return false;
    }
  }
  return true;
}


// implement member functions for derived classes
double Sin::eval(double x) const {
  return std::sin(get_left()->eval(x));
}
double Cos::eval(double x) const {
  return std::cos(get_left()->eval(x));
}

double Plus::eval(double x) const{
  if(get_right() == nullptr){
    return get_left()->eval(x);
  }
  return get_left()->eval(x) + get_right()->eval(x);
}
double Minus::eval(double x) const{
  return get_left()->eval(x) - get_right()->eval(x);
}
double Multiply::eval(double x) const{
  if(get_right() == nullptr){
    return get_left()->eval(x);
  }
  return get_left()->eval(x) * get_right()->eval(x);
}
double Divide::eval(double x) const{
  double checknotzero = get_right()->eval(x);
  if(checknotzero){
     return get_left()->eval(x) / get_right()->eval(x);
  }
  else{
    throw PlotException("Divide by Zero");
  }
}