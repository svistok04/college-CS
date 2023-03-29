//
// Created by marling on 3/22/23.
//

#ifndef LAB4_TREE_HPP
#define LAB4_TREE_HPP

#include <string>

class Tree {
private:
    int height;
    std::string color;
    char symbol;
    int x, y;
    char** tab;

public:
    Tree(int, std::string, char, int, int);
    ~Tree();

    friend class Forest;
};


#endif //LAB4_TREE_HPP
