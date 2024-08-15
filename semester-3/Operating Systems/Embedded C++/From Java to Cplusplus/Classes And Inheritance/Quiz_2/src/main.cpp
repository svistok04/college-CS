#include <iostream>

class A {
public:
    A() { std::cout << "A" << std::endl; }
    virtual void f() { std::cout << "Af" << std::endl; }
};

class B : public A {
public:
    B() { std::cout << "B" << std::endl; }
    void f() override { std::cout << "Bf" << std::endl; }
};

class C : public B {
public:
    C() { std::cout << "C" << std::endl; }
    void f() { std::cout << "Cf" << std::endl; }
};

int main() {
    A a;
    B b;
    C c;
    A& a2 = b;
    a2.f();
    A& a3 = c;
    a3.f();
    return 0;
}