#ifndef READER_H
#define READER_H
#include <iostream>
#include "plot.h"

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  Reader();
  ~Reader();

  // read plot description from given istream;
  // throw a PlotException if any errors are found

  int read_input(std::istream &in, Plot &plot);

  //helper methods for reading the file
  void read_plot(std::stringstream &ss, std::vector<std::string> &params,std::string &temp,Plot &plot);//reads lines that start with Plot
  void read_func(std::stringstream &ss, Plot &plot, int &func_counter);//reads lines that start with Function
  void read_color(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, int &func_counter, std::string &temp);//reads lines that start with Color
  void read_fillabovebelow(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, std::string &temp,std::string &state);//reads lines that start with FillAbove and Fill Below
  void read_fillbetween(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, std::string &temp);//reads lines that start with FillBetween
};

#endif // READER_H
