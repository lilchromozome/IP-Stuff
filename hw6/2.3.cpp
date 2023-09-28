#include <iostream>
#include <map>

int main(){
typedef std::map<char, int> CIMap;
const char arr[] = "hooray";
CIMap m;
for (int i = 0; i < 5; i++) {
  m[arr[i]] = (i + 1);
}

for (CIMap::const_reverse_iterator i = m.crbegin();
     i != m.crend();
     i++) {
  std::cout << i->first << "," << i->second << std::endl;
}
std::cout << m['z'] << std::endl;
std::cout << m.size() << std::endl;
}

/*
r,4
o,3
h,1
a,5
0
5

prints dictionary in reverse order, when dictionary elements added
they are sorted automatically
then create and print instance 'z'
number of elements is 5 a, h, o, r, z
*/