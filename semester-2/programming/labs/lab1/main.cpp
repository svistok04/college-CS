//
// Created by marling on 3/25/23.
//
#include <iostream>

using namespace std;

class Fruit {
    string name;
public:
    string getName();
};

int main()
{
    Fruit jablko;
    // jablko.name = "jablko";
    cout << jablko.getName();
}

string Fruit::getName() {
    name = "jablko";
    return name;
}