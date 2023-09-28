#include <iostream>

class Foo {
public:
  int field = 0;
};

int main() {
    Foo f;
  std::cout << f.field;
  return 0;
}

/*
In the line Foo.field, Foo does not refer to any object so the . operator is invalid. You cannot just refer to the entire class. Therefore, to access field first create an object of class Foo, then call .field on the object.
For example
Foo f;
std::cout << f.field;
*/