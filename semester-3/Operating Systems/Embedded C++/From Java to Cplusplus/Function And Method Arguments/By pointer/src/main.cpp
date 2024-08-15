#include <iostream>
#include <string>

void addOne(int *i) {
    // Actually changes the original variable, but i can be null !
    (*i)++;
}

void changeFirst(std::string *s) {
    // Actually changes the original variable
    s->at(0) = '#';
}

int main() {
    int i = 0;
    addOne(&i);
    std::cout << "Value of i is " << i << std::endl;

    std::string s("Hello");
    changeFirst(&s);
    std::cout << "Value of s is " << s << std::endl;
    return 0;
}