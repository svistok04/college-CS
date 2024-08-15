#include <iostream>

// Global variable
int globalVariable = 9;

// This variable scope is limited to this file
static int restrictedGlobalVariable = 10;

// Function using global variable
void f() {
    globalVariable += 1;
    restrictedGlobalVariable += 1;
}

int main() {
    std::cout << globalVariable << " " << restrictedGlobalVariable << std::endl;
    globalVariable++;
    restrictedGlobalVariable++;
    std::cout << globalVariable << " " << restrictedGlobalVariable << std::endl;
    f();
    std::cout << globalVariable << " " << restrictedGlobalVariable << std::endl;
    return 0;
}