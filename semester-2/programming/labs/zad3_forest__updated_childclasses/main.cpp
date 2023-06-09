#include <iostream>
using namespace std;

#include "Forest/Forest.hpp"


int main()
{

    Forest forest(24, 70);
    forest.addArea();

    /*  auto tree1 = new Tree_old(5, "green", '*');
      auto tree2 = new Tree_old(3, "red", '\\');
      tree1->printTree();

      forest.addTree(tree1);
      forest.addTree(tree2); */

  auto rect1 = new Rectangle(5, 9, "red", '*', 18, 20);

  auto rect2 = new Rectangle(5, "red", '\\', 10, 10);


  auto triangle1 = new Triangle(6, "green", '*', 13, 19);

  auto rtriangle1 = new RightTriangle(5, "green", '*', 2, 2);

  auto border1 = new Border(5, "yellow", '*', 16, 40);
/*
  border1->Print();

  cout << "\n";

  triangle1->Print();

  cout << "\n";

  rtriangle1->Print();

  cout << "\n";

  rect1->Print();
*/
  forest.addShape(triangle1);
  forest.addShape(rtriangle1);
  forest.addShape(rect1);
  forest.addShape(rect2);
  forest.addShape(border1);

  forest.printForest();

}