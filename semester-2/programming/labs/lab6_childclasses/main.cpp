#include <iostream>
#include "Shape.hpp"
#include "Rectangle.hpp"
using std::cout;

int main()
{

    Rectangle obj1(3, "green", '*');
    Rectangle obj2(5, 4, "yellow", '*');

    obj1.Print();
    cout << "\n";
    obj2.Print();
}