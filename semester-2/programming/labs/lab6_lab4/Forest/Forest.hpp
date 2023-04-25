//
// Created by marling on 3/29/23.
//

#ifndef LAB4_FOREST_HPP
#define LAB4_FOREST_HPP
#include <vector>
#include "../Tree/Tree.hpp"
#include "../Rectangle/Rectangle.hpp"
#include "../RightTriangle/RightTriangle.hpp"
#include "../Triangle/Triangle.hpp"
#include "../Border/Border.hpp"
#include "../Shape/Shape.hpp"

class Forest {
private:
    std::vector<Shape*> wektor;
    int height, width;
    char** forest{};

public:
    //void addTree(Tree*);
    void addShape(Shape*);
    void printForest();
    void addArea();
    Forest(int, int);
    ~Forest();

    friend class Tree;
};

#endif //LAB4_FOREST_HPP
