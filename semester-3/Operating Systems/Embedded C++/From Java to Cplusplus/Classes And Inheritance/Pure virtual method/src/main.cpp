#include <iostream>

class Abstract {
public:
    // Virtual method
    virtual void m1() {
        std::cout << "m1 in Abstract class called" << std::endl;
    }
    // Pure virtual method
    virtual void m2() = 0;
};

class Concrete : public Abstract {
public:
    // Override of the pure virtual method
    void m2() override { // 'override' is optional
        std::cout << "m2 in Concrete class called" << std::endl;
    }
};

int main() {
    // It is not possible to create an instance of Abstract
    // Abstract a;
    Concrete c;

    // Virtual method call through reference
    c.m1(); // prints Abstract
    c.m2(); // prints Concrete

    // C can be viewed as a reference to the Abstract class
    Abstract& a1 = c;
    a1.m1(); // prints Abstract
    a1.m2(); // prints Concrete

    return 0;
}