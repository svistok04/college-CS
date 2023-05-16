//
// Created by marling on 5/16/23.
//

#ifndef ZAD5_STL_TEAM_HPP
#define ZAD5_STL_TEAM_HPP
#include <iostream>

class Team {
    std::string name;
    int wins;
    int draws;
    int losses;
    int goalsScored;
    int goalsConceded;
    int score;

public:
    Team(std::string name, int wins, int draws, int losses, int goalsScored, int goalsMissed);
    ~Team();

    void scoreCalculation();

    const std::string &getName() const;
    int getWins() const;
    int getDraws() const;
    int getLosses() const;
    int getGoalsScored() const;
    int getGoalsConceded() const;
    int getScore() const;

    friend std::ostream& operator<<(std::ostream&, const Team&);
    static bool sortTeams(const Team&, const Team&);

};


#endif //ZAD5_STL_TEAM_HPP
