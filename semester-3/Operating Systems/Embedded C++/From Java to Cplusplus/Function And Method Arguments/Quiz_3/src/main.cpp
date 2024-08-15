#include <iostream>

class Dummy {
public:
    int x = 0;
};

void f(int &i, Dummy *d) {
    i = i + 1;
    d->x++;
}

int main() {
    Dummy d;
    int i = 2;
    f(i, &d);
    std::cout << d.x;
    return 0;
}