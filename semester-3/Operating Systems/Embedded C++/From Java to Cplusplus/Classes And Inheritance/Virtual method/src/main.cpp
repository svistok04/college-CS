#include <iostream>

class Base {
public:
    virtual void f() {
        std::cout << "f() in Base class called" << std::endl;
    }
};

class Derived : public Base {
public:
    void f() override { // 'override' keyword is optional
        std::cout << "f() in Derived class called" << std::endl;
    }
};

int main() {
    Base b;     // Create a base instance
    Derived d;  // Create a derived instance
    b.f();      // Prints base
    d.f();      // Prints derived

    // Virtual method call through reference
    Base& br = b;   // The type of br is Base&
    Base& dr = d;   // The type of dr is Base& as well
    br.f();         // Prints base
    dr.f();         // Prints derived (because Base::f() is declared as virtual)

    // Virtual method call through pointer
    Base* bp = &b;  // The type of bp is Base*
    Base* dp = &d;  // The type of dp is Base* as well
    bp->f();        // Prints base
    dp->f();        // Prints derived (because Base::f() is declared as virtual)

    // Non-virtual method calls
    br.Base::f();   // prints base
    dr.Base::f();   // prints base

    return 0;
}