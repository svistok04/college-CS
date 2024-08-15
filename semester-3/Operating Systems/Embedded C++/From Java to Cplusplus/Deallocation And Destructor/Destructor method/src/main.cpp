#include <iostream>

class Point {
public:
    // constructors
    Point() : _x(0), _y(0) {
        std::cout << "Point default constructor called" << std::endl;
    }
    Point(float x, float y) : _x(x), _y(y) {
        std::cout << "Point constructor called" << std::endl;
    }

    // destructor
    ~Point() {
        std::cout << "Point destructor called" << std::endl;
    }

    // public methods
    void move(float dx, float dy) {
        _x += dx;
        _y += dy;
    }
    float x() { return _x; }
    float y() { return _y; }

private:
    // private data fields
    float _x;
    float _y;
};

int main() {
    std::cout << "Begin of the program" << std::endl;
    Point p1(1, 2);

    Point* p2 = new Point(2, 3);
    delete p2;
    p2 = nullptr;

    std::cout << "End of the program" << std::endl;

    return 0;
}