#include <iostream>

class Foo {
public:
  int getVal() const { return _val; }
  Foo(int val) :_val(val){}
private:
  int _val;
};

int main() {
  Foo bar(10);
  std::cout << "my foo's val is " <<
       bar.getVal() << std::endl;
  return 0;
}

/*
The line Foo bar(10); calls the a constructor of class foo however there is no non-default constructor. The default constructor takes no arguments so there is a compile error when you try to pass a value to the declaration of bar. You could fix this by adding a non-default constructor to Foo.
For example under public:
Foo(int val) : val_val(val){}
*/