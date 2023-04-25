//
// Created by marling on 4/25/23.
//

#ifndef LAB6_LAB4_BORDER_HPP
#define LAB6_LAB4_BORDER_HPP

#include "../Shape/Shape.hpp"

class Border : public Shape
{
public:
    using Shape::Shape;
    virtual void Fill();
    Border(int, int, const std::string&, char, int, int);
    Border(int, const std::string&, char, int, int);
};


#endif //LAB6_LAB4_BORDER_HPP
