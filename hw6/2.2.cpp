#include <iostream>
#include <vector>

  int main(){
  typedef std::vector<int> IVec;
  IVec v1, v2;
  for (int i = 1; i <= 10; i++) { v1.push_back(i); }
  int count = 0;
  for (IVec::const_iterator j = v1.cbegin(); 
        j != v1.cend(); 
        j++, count++) {
    if (count < 5) {
      v2.insert(v2.begin(), *j);

    } else {
      v2.push_back(*j);
    }
  }

  for (IVec::const_iterator k = v2.cbegin();
       k != v2.cend();
       k++) {
    std::cout << *k << " ";
  }
  std::cout << std::endl;
}

/*
5 4 3 2 1 6 7 8 9 10
print numbers 1-5 in reverse, then append numbers 6-10
*/