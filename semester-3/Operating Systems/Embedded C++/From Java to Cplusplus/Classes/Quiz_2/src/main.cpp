#include <string>

class Dummy {
public:
    // constructors
    Dummy() : _number(-1), _s("a") { }
    Dummy(int number) : _number(number), _s("b") { }
    Dummy(std::string s) : _number(1), _s(s) { }

private:
    // private data fields
    std::string _s;
    int _number;
};

int main() {
    Dummy d1;
    Dummy d2(2);
    Dummy d3("Toto");
    return 0;
}