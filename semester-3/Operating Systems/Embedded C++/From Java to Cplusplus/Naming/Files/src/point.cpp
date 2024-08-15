#include "point.hpp"

Point::Point() : _x(0), _y(0) {
}


Point::Point(float x, float y) : _x(x), _y(y) {
}

void Point::move(float dx, float dy) {
    _x += dx;
    _y += dy;
}

float Point::x() const {
    return _x;
}

float Point::y() const {
    return _y;
}
