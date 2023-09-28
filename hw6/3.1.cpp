#include <iostream>
#include <vector>

using namespace std;
using vit = vector<string>::const_iterator;

void print(const vector<string>& s) {
  for(vit it = s.begin(); it != s.end(); ++it ) { 
    cout << *it << endl; 
  }
}

/*
The code has a compile error because the iterator it iterates through a const vector as a non-const iterator. Therefore by declaring vit as vector <string>::const_iterator instead of iterator should fix the issue in print.
*/