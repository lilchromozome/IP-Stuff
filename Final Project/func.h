#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"

class Function {
private:
  // a function has a name and an expression computing its value (given x)
  std::string m_name = "";
  Expr *m_expr = nullptr;
  
  // value semantics prohibited
  Function(const Function &);
  Function &operator=(const Function &);

  friend struct expr_test;
public:
  //Constructors
  Function(){m_name = "";m_expr = nullptr;}
  Function(const std::string &name, Expr *expr);
  //Destructor
  ~Function();
  
  //Getter and Setter methods
  std::string get_name() const;
  Expr *get_expr() const;
  void set_name(const std::string &name);
  void set_expr(Expr *expr);
  

  double eval(double x) const;//evalutates the function given a value x
};

#endif // FUNC_H
