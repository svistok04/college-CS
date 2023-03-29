//
// Created by marling on 3/29/23.
//

#ifndef LAB4_NEW_TREE_HPP
#define LAB4_NEW_TREE_HPP

#include <string>

class Forest;

class Tree {
private:
    int height;
    std::string color;
    char symbol;
    int x, y;
    char **tab;

public:
    Tree(int, std::string, char, int, int);
    ~Tree();

    friend class Forest;
};


#endif //LAB4_NEW_TREE_HPP
