#include <iostream>
using namespace std;

#include "Tree/Tree.hpp"
#include "Forest/Forest.hpp"
#include "Tree_old/Tree_old.hpp"


int main()
{
/*
    Tree_old tree(5, "green", '*');
    tree.printForest();
*/

    Forest forest(15, 20);
    forest.addArea();

    Tree* tree1 = new Tree(5, "green", '/', 2, 2);
    Tree* tree2 = new Tree(3, "red", '\\', 10, 10);

    forest.addTree(tree1);
    forest.addTree(tree2);

    forest.printForest();

}