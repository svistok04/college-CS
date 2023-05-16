//
// Created by marling on 5/16/23.
//

#ifndef ZAD4_WHEELGAME_GAME_HPP
#define ZAD4_WHEELGAME_GAME_HPP

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include "../Player/Player.hpp"
#include "../Wheel/Wheel.hpp"

using namespace std;


class Game {
public:
    Game();
    ~Game();

    void play();

private:
    int jestSamogloska(char c);
    char WczytajZnak();
    char WczytajWybor();
    void wczytaczHaslo();
    void textPlayers();
    friend ostream& operator<<(ostream& os, const Player& player);

    string haslo;
    string proba;
    string rezultat;
    vector<string> hasla;
    vector<Player> gracze;
    int rozmiar;
    int maska[100];
    char wybor;
    char literka;
    int kolejka = 0;
    int suma = 0;
    int zgadl = 0;
    int sa_spolgloski = 0;
    int kwota = 0;
};

#endif //ZAD4_WHEELGAME_GAME_HPP
