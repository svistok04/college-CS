// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <ncurses.h>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <clocale>

using namespace std;
#include "Game/Game.hpp"


int main()
{
    Game game;
    game.play();
}