#include <iostream>
#include <vector>
#include <algorithm>
#include "Player/Player.hpp"

void fun(Player);

int main() {
    Player player("Nowak", 20);

    std::vector<Player> team;
    team.push_back(player);

    std::ifstream file("dane.txt");

    while(file >> player) {
        //std::cout << player;
        team.push_back(player);
    }

    file.close();

    std::ofstream file2("out.txt");

    //for_each(team.begin(), team.end(), fun);
    //for_each(team.begin(), team.end(), player()); //doesn't work :((
    for_each(team.begin(), team.end(), [](Player p) {std::cout << p << std::endl;} ); //lambda

    for(auto p : team) {
        file2 << p;
    }

    std::vector<Player>::iterator it;
    for(it=team.begin(); it != team.end(); it++) {
        std::cout << "iterator: " << *it << "\n";
    }

    std::cout << std::count_if(team.begin(), team.end(), [=](Player p) -> bool
    {return p.getNazwisko() == "Nowak"; });

    file2.close();

    return 0;
}

void fun(Player p) {
    std::cout << p << std::endl;
}