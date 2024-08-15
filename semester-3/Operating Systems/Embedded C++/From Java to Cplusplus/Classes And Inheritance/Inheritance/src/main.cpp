#include <iostream>

class Base1 {
public:
    Base1() {
        std::cout << "Base1 constructor" << std::endl;
    }
};

class Base2 {
public:
    Base2(int x) {
        std::cout << "Base2 constructor" << std::endl;
    }
};

class Derived : public Base1, Base2 {
public:
    Derived(int x) : Base2(x) {
        std::cout << "Derived constructor" << std::endl;
    }
};

int main() {
    Derived d(2);  // The Derived class extends Base1 and Base2
    return 0;
}