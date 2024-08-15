#include <iostream>
#include <string>

void addOne(int &i) {
    // Actually changes the original variable
    i++;
}

// Function overloading doesn't work here, so we have to change the name
void addOne_val(int i) {
    // Has no effect outside this scope because this is a copy of the original
    i++;
}

void changeFirst(std::string &s) {
    // Actually changes the original variable
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