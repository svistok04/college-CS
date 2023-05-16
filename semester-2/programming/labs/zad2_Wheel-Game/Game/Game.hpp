//
// Created by marling on 4/5/23.
//

#ifndef LAB6_GAME_HPP
#define LAB6_GAME_HPP

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
    static int jestSamogloska(char c);
    static char WczytajZnak();
    static char WczytajWybor();
    void wczytacHaslo();
    void textPlayers();
    void turnTheWheel();
    void zgadacHaslo();
    void zgadacLiterke();

    string haslo;
    string proba;
    string rezultat;
    vector<string> hasla;
    Player* gracze[3]{};
    int rozmiar{};
    int maska[100]{};
    char wybor{};
    char literka{};
    int kolejka = 0;
    int suma = 0;
    int zgadl = 0;
    int sa_spolgloski = 0;
    int kwota = 0;
};


#endif //LAB6_GAME_HPP
