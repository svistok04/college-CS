#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "Team/Team.hpp"
int main() {
    std::vector <Team> league = {
            {"Team1", 4, 18, 6, 23, 55},
            {"Team2", 8, 14, 7, 30, 45},
            {"Team3", 0, 22, 5, 10, 65},
            {"Team4", 16, 4, 5, 60, 25},
            {"Team5", 6, 16, 8, 28, 50},
            {"Team6", 4, 18, 6, 20, 60},
            {"Team7", 16, 4, 7, 45, 25},
            {"Team8", 12, 10, 6, 36, 35},
            {"Team9", 14, 8, 8, 42, 30},
            {"Team10", 10, 12, 9, 32, 40}
    };

    std::sort(league.begin(), league.end(),Team::sortTeams);
    std::cout << "Name  Score    Wins   Draws  Losses    Goals   Goals \n \t\t\t\t      Scored  Conceded\n";
    for(const auto& t : league)
        std::cout << t;
    return 0;
}
