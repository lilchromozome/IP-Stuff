#include <iostream>
#include <assert.h>

std::string mirror_str(const std::string &s) {
    std::string new_string(s);
    for(std::string::const_reverse_iterator it = s.crbegin(); it != s.crend(); it++){
        new_string.push_back(*it);
    }
    return new_string;
}

int main(){
    assert("Hello, world!!dlrow ,olleH" == mirror_str("Hello, world!"));
    assert("tacoocat" == mirror_str("taco"));

    std::cout << mirror_str("taco") << '\n';
}