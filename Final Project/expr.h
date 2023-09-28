#ifndef EXPR_H
#define EXPR_H

#include <cstddef>
#include <vector>
#include <cmath>
#include <iostream>

 /**
   * \brief Abstract class Expr used to create derived classes
  */
class Expr {
private:
  // field(s) to store links to child Expr nodes
  Expr* left = nullptr;
  Expr* right = nullptr;
  double val = 0.0;

  // testing purposes
  friend struct expr_test;
protected:
  void set_left(Expr* l) {left = l;}
  void set_right(Expr* r) {right = r;}
  void set_val(double v) {val = v;}


public:
  Expr* get_left() const{ return left;}
  Expr* get_right() const{ return right;}
  double get_val() const {return val;}
  
  Expr(Expr* left = nullptr, Expr* right = nullptr, double val = 0.0);
  virtual ~Expr();
  //pure function eval for subclasses
  virtual double eval(double x) const = 0;
  void deleteRecursive(Expr* &top);
  
  /**
    * \brief static Function isNumeric
    *
    * \detail This function loops through \param token and checks if each character is a digit or ".". If a "." already appeared, it will return false. If it reaches the end of the string with all tokens being numeric, it returns true.
    *
    * \param[in] token a string input
    *
    * \return true if it is a number, false if not
    */
  static bool isNumeric(std::string token);
};


// derived expression classes (possible nodes)

 /**
   * \brief class Variable derived from Expr represents x in a function y = f(x), it has no subnodes
  */
class Variable: public Expr{
  public:
    Variable(): Expr() {}
    /* virtual function returns the value x passed to it*/
    virtual double eval(double x) const override{
      return x;
    }
};

 /**
   * \brief class Constant derived from Expr, is assigned a constant value and has no subnodes
  */
class Constant: public Expr{
  public:
    Constant(double val): Expr(nullptr, nullptr, val) {}
 
   /* virtual function returns the value assigned to it every time */
    virtual double eval(double x) const override{
      x = this->get_val();
      return x;
    }
};

 /**
   * \brief class Sin derived from Expr, representing the sin function, must have 1 subnodes
  */
class Sin: public Expr{
  public:
    Sin(Expr* t): Expr(t) {}
    /* virtual function returns the sin of input x*/
    virtual double eval(double x) const override;
};

 /**
   * \brief class Cos derived from Expr, representing the cos function, must have 1 subnode
  */
class Cos: public Expr{
  public:
    Cos(Expr* t): Expr(t) {}
    /* virtual function returns the cos of input x*/
    virtual double eval(double x) const override;
};

 /**
   * \brief class Plus derived from Expr, representing the sum of 2 expressions, it has 2 subnodes but no restriction to number of operand expressions
   *
   * \detail if there are 1 or more items following a + in a prefix expression, eval will return the sum of all expressions. However, if there are no expressions following +, eval will return 0.
  */
class Plus: public Expr{
  public:
    Plus(Expr* l, Expr* r): Expr(l, r) {}
    /* virtual function returns the sum of 2 expression with input x*/
    virtual double eval(double x) const override;
};
 /**
   * \brief class Minus derived from Expr, representing the difference of 2 expressions, it must have 2 subnodes
   *
  */
class Minus: public Expr{
  public:
    Minus(Expr* l, Expr* r): Expr(l, r) {}  
    /* virtual function returns the difference of 2 expression with input x*/
    virtual double eval(double x) const override;
};
 /**
   * \brief class Multiply derived from Expr, representing the product of 2 expressions, it has 2 subnodes but no restriction to number of operand expressions
   *
   * \detail if there are 1 or more items following a * in a prefix expression, eval will return the product of all expressions. However, if there are no expressions following *, eval will return 1.
  */
class Multiply: public Expr{
  public:
    Multiply(Expr* l, Expr* r): Expr(l, r) {} 
    /* virtual function returns the product of 2 expression with input x*/
    virtual double eval(double x) const override;
};

 /**
   * \brief class Divide derived from Expr, representing the quotient of 2 expressions, it must have 2 subnodes
   *
  */
class Divide: public Expr{
  public:
    Divide(Expr* l, Expr* r): Expr(l, r) {} 
    /* virtual function returns the quotient of 2 expression with input x*/
    virtual double eval(double x) const override;
};

#endif // EXPR_H
