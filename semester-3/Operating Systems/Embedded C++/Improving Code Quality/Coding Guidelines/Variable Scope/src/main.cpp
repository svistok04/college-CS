#include <iostream>

// This code should not be taken as a good example.
// It demonstrates the problem of variable name hiding.

int x; // global x

void hide()
{
    int x; // local x hides global x
    {
        // if you type the statement below for declaring x again
        // this demonstrates how one can hide another variable declaration
        /* int x; // hides first local x */
        x = 22; // assign to second local x

        // access to first local x is not possible here
        std::cout << x << std::endl;

        // this uses global x before it is initialized
        x = ::x;
        std::cout << x << std::endl;
    }
    // this uses first local x before it is initialized
    std::cout << x << std::endl;
    x = 33; // assign to first local x
    std::cout << x << std::endl;
    // access to global scope x is possible with ::
    ::x = 22;
    std::cout << ::x << std::endl;
}
int* px = &x; // take address of global x

int main() {
    hide();
    std::cout << *px << std::endl;
}


