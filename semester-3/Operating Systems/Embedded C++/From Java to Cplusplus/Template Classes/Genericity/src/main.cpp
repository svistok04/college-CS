#include <cstdio>

class Arithmetic {
public:
    Arithmetic(int a, int b) : _a(a), _b(b)
    {
    }

    int add()
    {
        return _a + _b;
    }

    int sub()
    {
        return _a - _b;
    }

private:
    int _a;
    int _b;
};

int main() {
    Arithmetic a1(1, 2);
    printf("Add is %d, sub is %d\n", a1.add(), a1.sub());

    // Put your code here
    return 0;
}