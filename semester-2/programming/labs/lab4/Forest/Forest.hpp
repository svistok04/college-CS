//
// Created by marling on 3/29/23.
//

#ifndef LAB4_FOREST_HPP
#define LAB4_FOREST_HPP
#include <vector>
#include "../Tree/Tree.hpp"

class Forest {
private:
    std::vector<Tree*> wektor;
    int height, width;
    char** forest;

public:
    void addTree(Tree*);
    void printForest();
    void addArea();
    Forest(int, int);
    ~Forest();

};

#endif //LAB4_FOREST_HPP
