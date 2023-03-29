//
// Created by marling on 3/29/23.
//

#ifndef LAB4_TREE_OLD_HPP
#define LAB4_TREE_OLD_HPP
#include <string>

class Tree_old {
private:
    int height;
    std::string color;
    char symbol;
    char** tab;

public:
    void printTree();
    Tree_old(int, std::string, char);
    ~Tree_old();
};



#endif //LAB4_TREE_OLD_HPP
