//
// Created by marling on 3/25/23.
//

#include <iostream>
using namespace std;

#include "Car.hpp"
#include "Fruit.hpp"


int main()
{
    Fruit apple("Apple", "Red");
    // jablko.name = "jablko";
    apple.getName();
    apple.getColor();

    cout << endl;

    Car volvo("Volvo", "Red", 'd');
    volvo.getName();
    volvo.getColor();
    cout << "i chto??" << endl;
    volvo.getFuelType();
}