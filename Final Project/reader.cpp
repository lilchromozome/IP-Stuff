#include <cstddef>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"
#include <memory>
#include <stdexcept>
#include <string>


Reader::Reader() {

}

Reader::~Reader() {

}

int Reader::read_input(std::istream &in, Plot &plot) {
  std::vector<std::string> input;
  std::string line; 
  std::string temp;
  std::string state;
  int func_counter = 0;
  
  while (std::getline(in, line)){//reads all lines of the file and put it in to a vector
    input.push_back(line);
  }

  try{
    for(size_t i = 0; i< input.size(); i++){// iterate through the lines
      std::stringstream ss(input[i]);
      std::vector<std::string> params; 
      ss>>state;
      
      /* Read Plot */
      if(state == "Plot"){
        read_plot(ss, params, temp, plot);
      }

      /* Read Function */
      else if (state == "Function"){
        read_func(ss, plot, func_counter);
      }

      /* Read Color */
      else if (state == "Color"){
        read_color(ss, params, plot, func_counter, temp);
      }

      /* Read FillAbove and FillBelow */
      else if (state == "FillAbove" || state == "FillBelow"){
        read_fillabovebelow(ss, params, plot, temp, state);
      }

      /* Read FillBetween */
      else if(state == "FillBetween"){
        read_fillbetween(ss, params, plot, temp);
      }

      /* Invalid State */
      else{
          throw PlotException("Error: invalid input");
      }
    }
  }

  catch(PlotException& e){
    std::cerr << "Error: " << e.what() << std::endl;
    exit(1);
  }
  
  return 0;
}

void Reader::read_plot(std::stringstream &ss, std::vector<std::string> &params, std::string &temp, Plot &plot){
  while(ss >> temp){//parse the line
    params.push_back(temp);
  }

  if(params.size() != 6){//check if the correct number of argument is given
    throw PlotException("Wrong number of arguments for Plot");
  }

  try{
    double x_min = std::stod(params.at(0));
    double y_min = std::stod(params.at(1));
    double x_max = std::stod(params.at(2));
    double y_max = std::stod(params.at(3));
    if(x_max < x_min || y_max < y_min){//check if bounds values are valid
      throw PlotException("Invalid plot bound");
    }
    plot.set_bounds(x_min, x_max, y_min, y_max);//Inialize bounds
    
    double x_dim = std::stod(params.at(4));
    double y_dim = std::stod(params.at(5));
    if(x_dim < 0 || y_dim < 0){//check if dimension values are valid
      throw PlotException("Invalid image dimensions");
    }
    plot.set_dimensions(x_dim, y_dim);//Inialize Image dimensions
    }

  catch(std::invalid_argument& e){
      throw PlotException("Invalid argument");
  }
}

void Reader::read_func(std::stringstream &ss, Plot &plot, int &func_counter){
  std::string name;
  Expr *expr;
  ExprParser* expr_parser = new ExprParser();
  ss>>name;
  std::stringstream remaining;//Make new string stream and parse
  std::string word;
  
  while (ss >> word) {
    remaining << word << " ";
  }

  expr = expr_parser->parse(remaining);//parse the expr
  plot.add_function(name, expr);//Add function to the end of the funcs array
  func_counter++;
  delete expr_parser;
}

void Reader::read_color(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, int &func_counter, std::string &temp){
  std::stringstream sserr;
  plot.resize_color(func_counter);//sets the size of the color array to be the same as the length fo the function array
  plot.resize_color_init(func_counter);//sets the size of the color_init array to be the same as the length fo the function array
  std::string name;
  while(ss >> temp){
    params.push_back(temp);
  }
  if(params.size() != 4){//check if the correct number of argument is given
    throw PlotException("Wrong number of arguments for Color");
  }
  
  name = params.at(0);

  try{
  int r = std::stoi(params.at(1));
  int g = std::stoi(params.at(2));
  int b = std::stoi(params.at(3));
  Color color(r, g, b);

  if(plot.get_color(plot.get_func_pos(name)) != Color()){//Check if funciton already has color
    sserr << "Function " << name << " already has Color";
    throw PlotException(sserr.str());
  }

  plot.set_color_init(plot.get_func_pos(name)); //Set initlized to true
  plot.add_color(color, plot.get_func_pos(name));//Add color to the index of it's matching function 
  }

  catch(const std::invalid_argument& e){
    throw PlotException("Invalid argument");
  }

}

void Reader::read_fillabovebelow(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, std::string &temp, std::string &state) {
  Fill* new_fill = new Fill();
  while(ss >> temp){
    params.push_back(temp);
  }
  if(params.size() != 5){//check if the correct number of argument is given
    throw PlotException("Wrong number of arguments for Fill");
  }
  
  // add function to fill
  plot.get_func_pos(params.at(0));
  new_fill->add_function(&plot.get_func(params.at(0)));
  
  try{
  new_fill->set_opacity(std::stod(params.at(1)));//set the opacty for fill
  int r = std::stoi(params.at(2));
  int g = std::stoi(params.at(3));
  int b = std::stoi(params.at(4));
  Color color(r, g, b);
  new_fill->set_color(color);//set the color for fill
  
  //set the fill type
  if (state == "FillAbove"){
    new_fill->set_type(1);
  }
  else if (state == "FillBelow"){
    new_fill->set_type(2);
  }

  plot.add_fill(*new_fill);//Add fill to the end of the fills vector
  
  delete new_fill;
  }
  catch(const std::invalid_argument& e){
    throw PlotException("Invalid argument");
  }
}

void Reader::read_fillbetween(std::stringstream &ss, std::vector<std::string> &params,Plot &plot, std::string &temp){
  Fill* new_fill = new Fill();
  while(ss >> temp){
    params.push_back(temp);
  }
  if(params.size() != 6){//check if the correct number of argument is given
    throw PlotException("Wrong number of arguments for Fill");
  }
  //Add functions to fill
  plot.get_func_pos(params.at(0));
  new_fill->add_function(&plot.get_func(params.at(0)));
  plot.get_func_pos(params.at(1));
  new_fill->add_function(&plot.get_func(params.at(1)));
  
  try{
    new_fill->set_opacity(std::stod(params.at(2)));//set the opacty for fill
    int r = std::stoi(params.at(3));
    int g = std::stoi(params.at(4));
    int b = std::stoi(params.at(5));
    Color color(r, g, b);
    new_fill->set_color(color);//set the color for fill
    new_fill->set_type(3);//set the type for fill
   
    plot.add_fill(*new_fill);//Add fill to the end of the fills vector
    
    delete new_fill;
  }
  catch(const std::invalid_argument& e){
    throw PlotException("Invalid argument");
  }
}