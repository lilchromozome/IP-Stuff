#include <ios>
#include <string>
#include <algorithm>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"


/**
  * \brief Dictionary to find each possible expression
  *
  * \detail each expression is an operator that checked after determining the expressino is not a constant or x
  */
const std::map<std::string, int> expressions = {
  std:: make_pair("sin", 1),
  std:: make_pair("cos", 2),
  std:: make_pair("+", 3),
  std:: make_pair("-", 4),
  std:: make_pair("*", 5),
  std:: make_pair("/", 6),
};

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}

 /**
   * \brief Function printDeque will print a deque to thr command line, used for debugging
   *
   * \param[in] in The deque of strings to be printed
   *
   * \return no return, prints strings to stdout
  */
void printDeque(std::deque<std::string> in){
  for(size_t i = 0; i < in.size(); i++){
    std::cout << in.at(i) << " ";
  }
  std::cout << std::endl;
}

 /**
   * \brief Function findSep to find where the 2 expression of a 2 operand operator is (+, -, *, /)
   *
   * \detail This function finds the dividing line between 2 operands, which will be the position of the last token of the first element. If neither operand is encompassed by (), it returns the position of the first operand. If the first operand does not have () encompassing it and the second does. It will return 0. If the second operand has () encompassing it and the first does not, it will return the last token of the first element. Otherwise, it returns the index of the last ) of the first operand.
   *
   * \param[in] tokens The deque of tokens
   *
   * \return int index of the last token of the first operand
  */
int findSep(std::deque<std::string> tokens){
  int countP = 0;      //count for ()
  for(size_t i = 0; i < tokens.size(); i++){
    if(tokens.at(i) != "(" && tokens.at(i) != ")"){
      if(countP == 0){ return i; }
      continue;
    }
    if(tokens.at(i) == "(") { countP++; }
    if(tokens.at(i) == ")") { countP--; }
    if(countP == 0) { return i; }
  }
  if(countP != 0)
    return -1;
  return tokens.size()-1;
}

std::deque<std::string> ExprParser::splitDeque(int start, int end, std::deque<std::string>& originalDeque) const{
    // create a subdeque from deque
    std::deque <std::string> newDeque;
    for (int i = start; i < end; i++) {
        newDeque.push_back(originalDeque.at(i));
    }
    return newDeque;
}

 /**
   * \brief Function checkTokens to check parentheses are as expected and return show many expressions are in \param tokens
   *
   * \detail This function loops through tokens and counts the number of parentheses with countP, making sure that each "(" has a corresponding ")". If not, it will return -1. Each time the number of "(" matched the number of ")", there is a single expression. And all tokens in token while the number of parentheses are matched are also expressions, incrementing countE. At the end of tokens, if there are unequal number of parentheses, it will return -1, otherwise will return the number of tokens.
   *
   * \param[in] tokens The deque of tokens
   *
   * \return int -1 if parentheses are unequal, otherwise return the number of tokens (countE) 
  */
int checkTokens(std::deque<std::string> tokens){
  int countP = 0;      //count for ()
  int countE = 0;      //count for expressions
  for(size_t i = 0; i < tokens.size(); i++){
    if(tokens.at(i) != "(" && tokens.at(i) != ")"){
      if(countP == 0) { countE++; }
      continue;
    }
    if(tokens.at(i) == "(") { countP++; }
    if(tokens.at(i) == ")"){ countP--; }
    if(countP == 0) { countE++; }
  }
  if(countP != 0)
    return -1;
  else{
    return countE;
  }
}


Expr *ExprParser::parse(std::istream &in) {
  std::deque<std::string> tokens;
  std::string token;
  while(in >> token){
    if(token == ")" && tokens.back() == "("){
      tokens.pop_back();
      continue;
    }
    tokens.push_back(token);
  }

  return parseHelper(tokens);
}


Expr *ExprParser::parseHelper(std::deque<std::string> &tokens){
try{
  if(tokens.empty()) 
    throw PlotException("Incomplete function");

  std::string t;
  t = tokens.front();
  tokens.pop_front();

  if(t == "("){
    if(tokens.back() == ")") {tokens.pop_back();}
    return(parseHelper(tokens));
  }

  /*Base cases of constant or variable*/
  if(t == "x" ){
    Variable* node = new Variable();
    return node;
  }
  else if (t == "pi" || Expr::isNumeric(t)) {
    /*convert t to a double*/
    t = (t == "pi") ? "3.14159265358979323846" : t;
    double val = std::stod(t);
    Constant* node = new Constant(val);
    return node;
  }
  if(expressions.find(t) == expressions.end()){
    throw PlotException("Unexpected Function token");
  }

  /*Recursive case of expressions sin, cos, +, -, *, / */
  size_t separator = 0;
  std::deque<std::string> left;
  std::deque<std::string> right;
  Expr* node;

  //try switch, catch out of bounds from separator givng bad data to split deque
  int operands = checkTokens(tokens);
  if(operands == -1)
    throw PlotException("invalid parentheses");
  switch (expressions.at(t)) {
    /*sin case*/
    case 1:
      if(operands != 1)
        throw PlotException("invalid number of arguments for sin");

      node = new Sin(parseHelper(tokens));
      return node;
    /*cos case*/
    case 2:
      if(operands != 1)
        throw PlotException("invalid number of arguments for cos");

      node = new Cos(parseHelper(tokens));
      return node;
    /*Plus case*/
    case 3:
      if(operands == 0){
        node = new Constant(0);
        return node;
      }
      else if(operands == 1){
        if(tokens.front() == "(" && tokens.back() == ")"){
          tokens.pop_back();
          tokens.pop_front();
          tokens.push_front("+");
        }
        node = new Plus(parseHelper(tokens), nullptr);
        return node;
      }
      separator = findSep(tokens);

      left = splitDeque(0, separator+1, tokens);
      right = splitDeque(separator+1, tokens.size(), tokens);
      if(checkTokens(right) > 1) { right.push_front("+"); }
      node = new Plus(parseHelper(left), parseHelper(right));
      return node;

    /*Minus case*/
    case 4:
      if(operands != 2)
        throw PlotException("invalid number of arguments for minus");
      separator = findSep(tokens);

      left = splitDeque(0, separator+1, tokens);
      right = splitDeque(separator+1, tokens.size(), tokens);
      
      node = new Minus(parseHelper(left), parseHelper(right));
      return node;
    /*Multiply case*/
    case 5:
      if(operands == 0){
        node = new Constant(1);
        return node;
      }
      else if(operands == 1){
        if(tokens.front() == "(" && tokens.back() == ")"){
          tokens.pop_back();
          tokens.pop_front();
          tokens.push_front("*");
        }
        node = new Multiply(parseHelper(tokens), nullptr);
        return node;
      }
      separator = findSep(tokens);

      left = splitDeque(0, separator+1, tokens);
      right = splitDeque(separator+1, tokens.size(), tokens);
      if(checkTokens(right) > 1) { right.push_front("*"); }
      node = new Multiply(parseHelper(left), parseHelper(right));
      return node;
    /*Divide case*/
    case 6:
      if(operands != 2)
        throw PlotException("invalid number of arguments for Divide");
      separator = findSep(tokens);
      left = splitDeque(0, separator+1, tokens);
      right = splitDeque(separator+1, tokens.size(), tokens);
      
      node = new Divide(parseHelper(left), parseHelper(right));
      return node;
    default:
      /* throw error, expression not valid */
      throw PlotException("Invalid Plot Directive");
      exit(33);
      break;
  }
}
  catch(PlotException& e){
    std::cerr << "Error: " << e.what() << std::endl;
    exit(1);
  }
  std::cerr << "Error: fell through" << std::endl;   //if everything falls through, bad throw error
  exit(1);
}