//
// Created by marling on 4/19/23.
//

#ifndef LAB6_TEST_PLAYER_H
#define LAB6_TEST_PLAYER_H

#include <iostream>


using std::string;

class Player {
private:
    string imie;
    int kasa = 0;
    int portfel = 0; //kasa z wygranych rund

public:
    int getPortfel();
    int getKasa();
    string getImie();
    void setPortfel(int);
    void setKasa(int);
    Player(string);
    ~Player();
};



#endif //LAB6_TEST_PLAYER_H
