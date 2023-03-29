//
// Created by marling on 3/29/23.
//

#ifndef LAB4_NEW_FOREST_HPP
#define LAB4_NEW_FOREST_HPP
#include <vector>
#include "../Tree/Tree.hpp"

class Forest {
private:
    std::vector<Tree *> wektor;
    char **forest;
    int height, width;

public:
    Forest( int h,  int w);
    ~Forest();
    void addTree(Tree *);
    void printForest();
    void addArea();
};


#endif //LAB4_NEW_FOREST_HPP
