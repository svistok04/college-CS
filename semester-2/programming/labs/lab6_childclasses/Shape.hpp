//
// Created by marling on 4/25/23.
//

#ifndef LAB6_SHAPE_HPP
#define LAB6_SHAPE_HPP

#include <string>

class Shape
{
public:
    void Print();
    virtual void Fill() = 0;
    void Alloc();
    Shape(int, std::string, char);
    ~Shape();
    static int counter;

    friend class Rectangle;

protected:
    int height;
    int width;
    std::string color;
    char symbol;
    char** tab;
    int x, y;



};



#endif //LAB6_SHAPE_HPP
