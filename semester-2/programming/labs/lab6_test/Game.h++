//
// Created by marling on 4/19/23.
//

#ifndef LAB6_TEST_GAME_H
#define LAB6_TEST_GAME_H

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include "Player/Player.h++"
#include "Wheel/Wheel.h++"

using namespace std;


class Game {
public:

    Game();

    void play();

private:
    int jestSamogloska(char c);
    char WczytajZnak();
    char WczytajWybor();
    void wczytaczHaslo();
    void textPlayers();
    void loadWords();
    void startRound();
    void endRound();
    void displayWord();
    void showMenu();
    void bankrupt();
    void roundLost();
    void roundWon();
    void turn();
    void gameOver();

    string haslo;
    string proba;
    string rezultat;
    vector<string> hasla;
    Player gracze[3];
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


#endif //LAB6_TEST_GAME_H
