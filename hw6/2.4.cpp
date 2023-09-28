#include <iostream>

int &max(std::pair<int, int> &p) {
  if (p.first > p.second) {
    return p.first;
  } else {
    return p.second;
  }
}

int main() {
  std::pair<int, int> p1, p2;

  p1 = std::make_pair(68, 12);
  p2 = std::make_pair(50, 59);

  std::cout << max(p1) << std::endl;
  std::cout << max(p2) << std::endl;
  max(p1) = 1;
  std::cout << max(p1) << std::endl;
}

/*
68
59
12          wot???, because max(p1) = 1 sets the reference variable to 1

prints bigger of 2 ints
max(p1) = 1 sets the bigger int to 1
when called again in cout, the pair is (1, 12)
*/