#include <iostream>

#define absolute_value(i) ( (i) >= 0 ? (i) : -(i) )

static int nbrOfCalls = 0;

int f() {
    nbrOfCalls++;
    return -1;
}

int main() {
    int x = -2;
    int ans1 = absolute_value(++x); // what is the value of ans1 ?
    int ans2 = absolute_value(f()); // how many times is f() called?

    std::cout << "Value of ans1 is " << ans1 << std::endl;
    std::cout << "Nbr of calls of f() is " << nbrOfCalls << std::endl;

    return 0;
}