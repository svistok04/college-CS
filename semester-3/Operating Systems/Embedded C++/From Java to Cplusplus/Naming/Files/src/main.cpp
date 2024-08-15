#include <iostream>
#include "point.hpp"

int main() {
    Point p1;
    std::cout << "(" << p1.x() << ", " << p1.y() << ")" << std::endl;
    Point p2(1, 2);
    p2.move(2, 3);
    std::cout << "(" << p2.x() << ", " << p2.y() << ")" << std::endl;
    return 0;
}