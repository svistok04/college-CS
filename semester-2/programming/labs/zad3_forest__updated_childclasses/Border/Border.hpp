//
// Created by marling on 4/25/23.
//

#ifndef LAB6_LAB4_BORDER_HPP
#define LAB6_LAB4_BORDER_HPP

#include "../Rectangle/Rectangle.hpp"

class Border : public Rectangle
{
public:
    using Rectangle::Rectangle;
    virtual void Fill();
    Border(int, int, const std::string&, char, int, int);
    Border(int, const std::string&, char, int, int);
};


#endif //LAB6_LAB4_BORDER_HPP
