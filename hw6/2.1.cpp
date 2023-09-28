#include <iostream>
#include <sstream>
#include <cmath>

int main(int argc, char* argv[]){
std::string s;
std::getline(std::cin, s);

std::stringstream ss1(s), ss2(s);
int total1 = 0, total2 = 0;
char c;
while (ss1.get(c)) {
  if (c >= '1' && c <= '9' && c%2!=0) {
    total1 += (c - '0');
  }
 }
int n;
while (ss2 >> n) {
  total2 += floor(log10(n) + 1);
}

std::cout << "total1=" << total1 << ", total2=" << total2 << std::endl;
}
/*
total1=9, total2=5

input: 12 3 45
For ss1, sum all odd digists
For ss2 sum the number of digits
*/