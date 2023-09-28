#include <iostream>
#include <string>

class SPair {
private:
  std::string s1, s2;
public:
  SPair() : s1("Hi!") { }

  const std::string get_s1() const { return s1; }
  const std::string get_s2() const { return s2; }
};

int main() {
  SPair sp;
  std::cout << sp.get_s1().length() << std::endl;
  std::cout << sp.get_s2().length() << std::endl;
}

/*
3
0

s1 = Hi! length = 3
s2 calls defaul string initializer with length = 0
*/