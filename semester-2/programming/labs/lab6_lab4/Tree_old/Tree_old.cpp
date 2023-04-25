//
// Created by marling on 3/22/23.
//

#include "Tree_old.hpp"
#include <iostream>
using namespace std;

void Tree_old::printTree()
{
    int i, j;

    if (color == "green") cout << "\u001b[1;32m";
    if (color == "red") cout << "\u001b[1;31m";

    tab = new char* [height];
    for (j = 0; j < height; j++) {
        tab[j] = new char[2 * height - 1];
        for (i = 0; i < 2 * height - 1; i++)
            tab[j][i] = ' ';
    }

    for (j = 0; j < height; j++)
        for (i = height - j - 1; i < height + j; i++)
            tab[j][i] = symbol;

    for (j = 0; j < height; j++) {
        for (i = 0; i < 2*height-1; i++) {
            cout << tab[j][i];
        }
        cout << endl;
    }

    if (color == "green") cout << "\u001b[0m";
    if (color == "red") cout << "\u001b[0m";

    /* simple solution
       for (j = 0; j <height; j++)
       {
           for (i = height - j - 1; i > 0; i--)
               cout << ' ';

           for (i = 0; i < 2*j+1; i++)
               cout << '*';

           cout << endl;
       }

       cout << endl << endl;

   */

    /* unrealized solution
      for(j = 0; j < height; i++)
      {
          int k = 2*j + 1;
          for(int i = 0; i < (height-k)/2; i++)
          {
              cout << " ";
          }
          for(int i = 0; i < k; i++)
          {
              cout << symbol;
          }
          for(int i = 0; i < (height-k)/2; i++)
          {
              cout << " ";
          }
          cout << endl;
      }
    */
}

Tree_old::Tree_old(int _height, string _color, char _symbol)
{
    height = _height;
    color = _color;
    symbol = _symbol;
};

Tree_old::~Tree_old() {
    int j;
    cout << "The tree has been removed" << endl;
    for (j = 0; j < height; j++) {
        delete tab[j];
    }
    delete tab;
}