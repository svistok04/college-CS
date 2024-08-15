#include <iostream>
#include <string>

void addOne(int i) {
    // Has no effect outside this scope because it's a copy from the original
    i++;
}

void changeFirst(std::string s) {
    // Has no effect outside this scope because it's a copy from the original
    s[0] = '#';
}

int main() {
    int i = 0;
    addOne(i);
    std::cout << "Value of i is " << i << std::endl;

    std::string s("Hello");
    changeFirst(s);
    std::cout << "Value of s is " << s << std::endl;
    return 0;
}