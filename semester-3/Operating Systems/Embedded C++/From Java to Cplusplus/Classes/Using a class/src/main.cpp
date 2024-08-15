#include <iostream>

class Point {
public:
    // constructors
    Point() : _x(0), _y(0) { }
    Point(float x, float y) : _x(x), _y(y) { }

    // public methods
    void move(float dx, float dy) {
        _x += dx;
        _y += dy;
    }
    float x() const { return _x; }
    float y() const { return _y; }

private:
    // private data fields
    float _x;
    float _y;
};

int main() {
    // Initialization of a point on the stack
    Point p1;
    std::cout << "p(" << p1.x() << ", " << p1.y() << ")" << std::endl;
    // Initialization of a point on the stack with the given values
    Point p2(1, 2);
    std::cout << "p(" << p2.x() << ", " << p2.y() << ")" << std::endl;
    // Initialization of a point on the heap
    Point* p3 = new Point();
    std::cout << "p(" << p3->x() << ", " << p3->y() << ")" << std::endl;
    // Initialization of a point on the heap with the given values
    Point* p4 = new Point(3, 4);
    std::cout << "p(" << p4->x() << ", " << p4->y() << ")" << std::endl;
    // Delete objects on the heap and reset the pointer values to nullptr
    delete p3;
    p3 = nullptr;
    delete p4;
    p4 = nullptr;
    return 0;
}