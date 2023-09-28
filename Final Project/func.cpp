#include "func.h"

Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) {
}
Function::~Function() {
  if(this->m_expr){
    delete m_expr;
  }
}
std::string Function::get_name() const { 
  return m_name; 
}

Expr* Function::get_expr() const { 
  return m_expr; 
}

void Function::set_name(const std::string &name) { 
  m_name = name; 
}

void Function::set_expr(Expr *expr){ 
  m_expr = expr; 
}

double Function::eval(double x) const{
  return m_expr->eval(x);
}