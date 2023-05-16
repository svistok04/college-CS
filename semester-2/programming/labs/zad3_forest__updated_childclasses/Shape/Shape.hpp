//
// Created by marling on 4/25/23.
//

#ifndef LAB6_LAB4_SHAPE_HPP
#define LAB6_LAB4_SHAPE_HPP

#include <string>

class Shape
{
public:
    virtual void Print();
    virtual void Fill() = 0;
    void Alloc();
    Shape(int, const std::string&, char, int, int);
    ~Shape();
    static int counter;


protected:
    int height;
    int width;
    std::string color;
    char symbol;
    char** tab{};
    int x{}, y{};

    friend class Forest;

};



#endif //LAB6_LAB4_SHAPE_HPP
