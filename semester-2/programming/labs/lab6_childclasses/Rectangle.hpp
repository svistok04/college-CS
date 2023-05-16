//
// Created by marling on 4/25/23.
//

#ifndef LAB6_RECTANGLE_HPP
#define LAB6_RECTANGLE_HPP


#include "Shape.hpp"
#include <iostream>

class Rectangle : public Shape
{
public:
    using Shape::Shape;
    virtual void Fill();
    Rectangle(int, int, std::string, char);
    Rectangle(int, std::string, char);
};


#endif //LAB6_RECTANGLE_HPP
