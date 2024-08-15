#include <iostream>

namespace A {
    class Example {
    public:
        void m() {
            std::cout << "m from namespace A" << std::endl;
        }
    };
}

namespace B {
    class Example {
    public:
        void m() {
            std::cout << "m from namespace B" << std::endl;
        }
    };
}

int main() {
    A::Example exampleA;
    B::Example exampleB;

    exampleA.m();
    exampleB.m();
    return 0;
}