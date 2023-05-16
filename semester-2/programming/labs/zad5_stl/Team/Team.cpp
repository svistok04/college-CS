//
// Created by marling on 5/16/23.
//

#include "Team.hpp"

#include <utility>

std::ostream& operator<<(std::ostream& os, const Team& t) {
    return os << t.name << "\t" << t.score <<  "\t\033[;32m" << t.wins << "\033[0m\t" << t.draws << "\t\033[1;31m"
       << t.losses << "\033[0m\t\033[;32m"
       << t.goalsScored << "\t\033[1;31m" << t.goalsConceded << "\033[0m\n";
}

void Team::scoreCalculation() {
    score = wins * 3 + draws;
}

Team::Team(std::string name, int wins, int draws, int losses,
           int goalsScored, int goalsMissed) : name(std::move(name)),
                                               wins(wins),
                                               draws(draws),
                                               losses(losses),
                                               goalsScored(
                                                                 goalsScored),
                                               goalsConceded(
                                                                 goalsMissed) {
    scoreCalculation();
}
bool Team::sortTeams(const Team& team1, const Team& team2){
    if (team1.getScore() != team2.getScore())
        return team1.getScore() > team2.getScore();
    if (team1.getWins() != team2.getWins())
        return team1.getWins() > team2.getWins();
    if (team1.getLosses() != team2.getLosses())
        return team1.getLosses() < team2.getLosses();
    if (team1.getGoalsScored() != team2.getGoalsScored())
        return team1.getGoalsScored() > team2.getGoalsScored();
    return team1.getGoalsConceded() < team2.getGoalsConceded();
}

const std::string &Team::getName() const {
    return name;
}

int Team::getWins() const {
    return wins;
}

int Team::getDraws() const {
    return draws;
}

int Team::getLosses() const {
    return losses;
}

int Team::getGoalsScored() const {
    return goalsScored;
}

int Team::getGoalsConceded() const {
    return goalsConceded;
}

int Team::getScore() const {
    return score;
}

Team::~Team() = default;


