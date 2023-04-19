//
// Created by marling on 4/5/23.
//

#ifndef LAB6_PLAYER_HPP
#define LAB6_PLAYER_HPP
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


#endif //LAB6_PLAYER_HPP
