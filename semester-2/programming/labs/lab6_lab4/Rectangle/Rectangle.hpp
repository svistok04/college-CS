//
// Created by marling on 4/25/23.
//

#ifndef LAB6_LAB4_RECTANGLE_HPP
#define LAB6_LAB4_RECTANGLE_HPP

#include "../Shape/Shape.hpp"

class Rectangle : public Shape
{
public:
    using Shape::Shape;
    virtual void Fill();
    Rectangle(int, int, const std::string&, char, int, int);
    Rectangle(int, const std::string&, char, int, int);
};


#endif //LAB6_LAB4_RECTANGLE_HPP
