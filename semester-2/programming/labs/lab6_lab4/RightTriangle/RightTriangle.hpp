//
// Created by marling on 4/25/23.
//

#ifndef LAB6_LAB4_RIGHTTRIANGLE_HPP
#define LAB6_LAB4_RIGHTTRIANGLE_HPP

#include "../Shape/Shape.hpp"

class RightTriangle : public Shape {
public:
    using Shape::Shape;
    virtual void Fill();
    RightTriangle(int, const std::string&, char, int, int);
};


#endif //LAB6_LAB4_RIGHTTRIANGLE_HPP
