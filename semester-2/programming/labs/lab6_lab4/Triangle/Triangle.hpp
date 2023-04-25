//
// Created by marling on 4/25/23.
//

#ifndef LAB4_TRIANGLE_HPP
#define LAB4_TRIANGLE_HPP

#include "../Shape/Shape.hpp"

class Triangle : public Shape {
public:
    using Shape::Shape;
    virtual void Print();
    virtual void Fill();
    Triangle(int, const std::string&, char, int, int);
};


#endif //LAB4_TRIANGLE_HPP
