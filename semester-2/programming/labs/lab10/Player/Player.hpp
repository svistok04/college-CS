//
// Created by marling on 5/17/23.
//

#ifndef LAB10_PLAYER_HPP
#define LAB10_PLAYER_HPP
#include <iostream>
#include <fstream>

class Player {
    std::string nazwisko;
    int wiek;

public:
    Player(std::string, int);

    friend std::istream& operator>>(std::istream&, Player&);
    friend std::ostream& operator<<(std::ostream&, Player&);
    friend std::ifstream& operator>>(std::ifstream&, Player&);
    friend std::ofstream& operator<<(std::ofstream&, Player&);
    void operator () ();

    const std::string getNazwisko() const;
};


#endif //LAB10_PLAYER_HPP
