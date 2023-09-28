#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include <map>
#include "expr.h"
#include <deque>

class ExprParser{
private:
  // value semantics are prohibited

  Expr* top_node;

  friend struct expr_test;
public:
  ExprParser();
  ~ExprParser();

 /**
   * \brief Function splitDeque to creates a string subdeque from index start to index end-1.
   *
   * \detail This function takes a deque and consructs a new string deque by copying data from the original deque starting at index starting and ending with index end-1.
   *
   * \param[in] start is the index for the start of deque to copy
   *
   * \param[in] end is the index for the end of deque to copy (excluded)
   *
   * \return A new string subdeque with values from index [start, end)
   */
std::deque<std::string> splitDeque(int start, int end, std::deque<std::string>& originalDeque) const;

 /**
   * \brief Function parse to split a string representing a function into its compartmented expression nodes
   *
   * \detail This function creates a string deque and inserts each word in the istream (in) into the deque as tokens. Then, it uses parsehelper, a recursive function to create the expression nodes. It returns a pointer to the topmost node.
   *
   * \param[in] in A reference to a istream object to parse into expressions
   *
   * \return A pointer to the topmost node
   */

Expr *parse(std::istream &in);      //maybe make this static? so reader can use

 /**
   * \brief Recursive function parseHelper called by parse to create each expressin node from an input deque.
   *
   * \detail This function first removes "(", ")" tokens from both sides of the deque if applicable. The next term should be a valid expression. It first checks if it is a constant or x, which would imply no further subexpressions and returns it. If not, the expression like sin has 1 operable subexpression while expression like + has 2 operable subexpressions. A pointer to new corresponding expression is created until the final expression is a constant or x. When creating the new expressions, parsehelper is recursively called in the constructor to build the expression tree. Finally, parsehelper will return a pointer to the expression node given at the beginning of its input string deque.
   *
   * \param[in] tokens a string deque holding all the tokens from the input istream
   *
   * \return A pointer to the expression refering to the beginning of the input deque.
   */
Expr *parseHelper(std::deque<std::string> &tokens);

Expr* get_top_node(){
  return top_node;
}
};

#endif // FN_PARSER_H