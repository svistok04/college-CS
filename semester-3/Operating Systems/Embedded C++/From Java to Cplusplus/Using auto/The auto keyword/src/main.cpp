#include <iostream>

int main() {
    // Put your code here
    auto a = true; // b is a boolean
    std::cout << "a is " << a << " " << typeid(a).name() << std::endl;
    auto b = 's'; // ch is a char
    std::cout << "b is " << b << " " << typeid(b).name() << std::endl;
    auto c = 1234; // i is an int
    std::cout << "c is " << c << " " << typeid(c).name() << std::endl;
    auto d = 1234L; // l is a long
    std::cout << "d is " << d << " " << typeid(d).name() << std::endl;

}