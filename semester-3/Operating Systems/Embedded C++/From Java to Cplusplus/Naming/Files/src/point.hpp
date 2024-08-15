#pragma once

#ifndef EMBEDDED_C__POINT_HPP
#define EMBEDDED_C__POINT_HPP

class Point {
public:
    // constructors
    Point();
    Point(float x, float y);

    // public methods
    void move(float dx, float dy);
    float x() const;
    float y() const;

private:
    // private data fields
    float _x;
    float _y;
};

#endif //EMBEDDED_C__POINT_HPP
