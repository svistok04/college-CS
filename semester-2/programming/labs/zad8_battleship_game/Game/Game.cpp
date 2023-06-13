//
// Created by marling on 6/6/23.
//

#include <random>
#include <iomanip>
#include <iostream>
#include "Game.hpp"

Player Game::getPlayer() {
    return player;
}

Computer Game::getComputer() {
    return computer;
}

std::string convertToLower(const std::string& str) {
    std::string lowercaseStr = str;
    std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowercaseStr;
}

std::ostream& operator<<(std::ostream& os, Game& game){

    Board playerBoard = game.getPlayer().getBoard();
    Board computerBoard = game.getComputer().getBoard();


    // print headers for user's and computer's boards
    os << std::setw(20) << "-Player-" << std::setw(55) << "-CPU-" << '\n';
    os << std::string(100, '-') << '\n';

    os << "     ";
    // print column letters for user's board
    for (char letter = 'A'; letter <= 'J'; letter++) {
        os << letter << "  ";
    }

    os << std::setw(22) << ' ';

    // print column letters for computer's board
    for (char letter = 'A'; letter <= 'J'; letter++) {
        os << letter << "  ";
    }

    os << std::endl;

    // Print board rows
    for (int i = 0; i < 10; i++) {
        // print row number for the user's board
        os << std::setw(4) << i + 1 << ' ';

        // print user's board row cells
        for (int j = 0; j < 10; j++) {
            Coordinates cord(0, 0);
            cord.setRow(i);
            cord.setColumn(j);
            if (playerBoard.getCell(cord).getHasShip()) std::cout << "\u001b[32m";
            if (playerBoard.getCell(cord).getHasBeenHit()) std::cout << "\u001b[31m";
            os << std::setw(2) << (playerBoard.getCell(cord).getHasShip() ? "& " : "— ") << ' ';
            if (playerBoard.getCell(cord).getHasShip() || playerBoard.getCell(cord).getHasBeenHit()) std::cout << "\u001b[0m";
        }

        // Add padding between boards
        os << std::setw(17) << ' ';

        // print row number for the computer's board
        os << std::setw(4) << i + 1 << ' ';


        // print computer's board row cells
        for (int k = 0; k < 10; k++) {
            Coordinates cord(0, 0);
            cord.setRow(i);
            cord.setColumn(k);
            if (computerBoard.getCell(cord).getHasBeenHit()) std::cout << "\u001b[31m";
            os << std::setw(2) << ((computerBoard.getCell(cord).getHasShip() && computerBoard.getCell(cord).getHasBeenHit()) ? "& " : "— ") << ' ';
            if (computerBoard.getCell(cord).getHasShip() || computerBoard.getCell(cord).getHasBeenHit()) std::cout << "\u001b[0m";

        }

        os << '\n';
    }

    return os;
}

void Game::askUserToPlaceShip(const std::string& name, const std::size_t& number) {
    Coordinates cord(0, 0);
    bool position = true; // true - horizontal, false - vertical
    std::string askPosition;
    std::string askPositionConverted;

    std::shared_ptr<Ship> ship = player.getShips()[number];
    std::string canBePlaced = "none";
    std::string askIfUserAgreesOnPosition;
    bool userAgreesOnPosition = false;

    std::vector<std::string> submarines = {"Submarine #1","Submarine #2", "#Submarine #3"};

    while (canBePlaced == "none" || !userAgreesOnPosition) {
        std::cout << "Choose location of " << name << ": ";
        std::cin >> cord;

        canBePlaced = player.getBoard().checkIfPossibleToPlace(cord, ship->getLength());

        if (canBePlaced == "none") {
            std::cout << "Sorry, but there's no way to place a ship with such a coordinate provided! Try again." << std::endl;
        }

        if (name != "Submarine #1" && name != "Submarine #2" && name!= "#Submarine #3") {
            if (canBePlaced == "both") {
                userAgreesOnPosition = true;
                while (askPositionConverted != "horizontal" && askPositionConverted != "vertical") {
                    std::cout << "Please, choose how you want to place your ship. Type the following: horizontal or vertical ";
                    std::cin >> askPosition;
                    askPositionConverted = convertToLower(askPosition);
                    if (askPositionConverted == "horizontal" || askPositionConverted == "vertical") canBePlaced = "ok";
                    position = (askPositionConverted == "horizontal");
                }
            } else if (canBePlaced == "vertical" || canBePlaced == "horizontal") {
                std::cout << "Unfortunately, a ship can be placed only " << (canBePlaced == "horizontal" ?
                "horizontally" : "vertically") << " with such coordinates. Do you agree to place it this "
                                                  "way? ""[y\\n]" << std::endl;
                while (askIfUserAgreesOnPosition != "y" && askIfUserAgreesOnPosition != "n") {
                    std::cin >> askIfUserAgreesOnPosition;
                    if (convertToLower(askIfUserAgreesOnPosition) == "y") {
                        userAgreesOnPosition = true;
                        position = (canBePlaced == "horizontal");
                    } else if (convertToLower(askIfUserAgreesOnPosition) == "n") {
                        userAgreesOnPosition = false;
                    } else {
                        std::cout << "Please, print y (for yes) or n (for no)!";
                    }
                }
            }
        } else {
            userAgreesOnPosition = true;
        }
    }


    ship->setCoordinates(cord, position);
    player.getBoard().placeShip(ship->getCoordinates());

    for (Coordinates& coord : ship->getCoordinates()) {
        player.getBoard().markCellsAsOccupied(coord);
    }
}
void Game::makeComputerPlaceShips(const std::size_t& number) {

    Coordinates coord(0, 0);
    std::string canBePlaced = "none";
    bool position;

    std::shared_ptr<Ship> ship = computer.getShips()[number];

    // create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // define distributions for random integers
    std::uniform_int_distribution<int> dist1(0, 9);
    std::uniform_int_distribution<int> dist2(0, 1);


    while(canBePlaced == "none") {
        int row = dist1(gen);
        int column = dist1(gen);
        coord.setRow(row);
        coord.setColumn(column);

        canBePlaced = computer.getBoard().checkIfPossibleToPlace(coord, ship->getLength());

        if (canBePlaced == "both") {
            position = dist2(gen);
        } else {
            position = (canBePlaced == "horizontal");
        }

    }

    ship->setCoordinates(coord, position);
    computer.getBoard().placeShip(ship->getCoordinates());

    for (Coordinates& coord : ship->getCoordinates()) {
        computer.getBoard().markCellsAsOccupied(coord);
    }

}

void Game::computerFire() {

    bool randomHit = false;

    std::random_device rd;
    std::mt19937 gen(rd());

    // define a distribution for random integers
    std::uniform_int_distribution<int> dist1(0, 9);
    std::uniform_int_distribution<int> dist2(0, 1);

    while(!randomHit) {
        int row = dist1(gen);
        int column = dist2(gen);

        Coordinates coord(row, column);

        if(!player.getBoard().getCell(coord).getHasBeenHit()) {
            randomHit = true;
            player.getBoard().getCell(coord).setHasBeenHit();
        }
    }
}

void Game::userFire() {
    Coordinates coord(0, 0);
    bool validInput = false;
    while(!validInput) {
        std::cout << "Type coordinates in order to shot enemy's ships! ";
        std::cin >> coord;
        if (computer.getBoard().getCell(coord).getHasBeenHit()) {
            std::cout << "This cell has already been hit by you! Try another!";
            continue;
        }
        validInput = true;
        computer.getBoard().getCell(coord).setHasBeenHit();
        if (computer.getBoard().getCell(coord).getHasShip()) {
            std::cout << "Hit!" << std::endl;
        } else {
            std::cout << "Miss!" << std::endl;
        }
    }
}

void Game::checkGameOver(std::vector<Coordinates>& computerCoords, std::vector<Coordinates>& userCoords) {
    Board& userBoard = player.getBoard();
    Board& computerBoard = computer.getBoard();

    bool userShipsRemaining = false;
    bool computerShipsRemaining = false;

    for(Coordinates& coord : userCoords) {
        if(!userBoard.getCell(coord).getHasBeenHit()) {
            userShipsRemaining = true;
            break;
        }
    }
    for (Coordinates& coord : computerCoords) {
        if(!computerBoard.getCell(coord).getHasBeenHit()) {
            computerShipsRemaining = true;
            break;
        }
    }

    if (!userShipsRemaining && computerShipsRemaining) {
        isGameOver = true;
        isUserWinner = false;
    }

    if(!computerShipsRemaining && userShipsRemaining) {
        isGameOver = true;
        isUserWinner = true;
    }

}


void Game::play() {


     std::vector<std::string> shipsNames = {"Carrier #1", "Battleship #1",
                                           "Cruiser #1", "Destroyer #1",
                                           "Destroyer #2", "Submarine #1",
                                           "Submarine #2", "#Submarine #3"
    };

    for (std::size_t i = 0; i < shipsNames.size(); i++) {
        makeComputerPlaceShips(i);
    }

    for (std::size_t i = 0; i < shipsNames.size(); i++) {

        std::string name = shipsNames[i];

        std::cout << "Welcome to BATTLESHIP Game!" << std::endl << std::endl;
        std::cout << "Please, whatever action you perform, enter the coordinates as follows:"
                     " <letter><number>." << std::endl << "Win by taking out all enemy ships before"
                                                          " you lose all of yours." << std::endl
                  << "Ships must be positioned at least "
                     "one cell away from each other, horizontally, vertically, and diagonally." << std::endl
                  << "Ships cannot touch or overlap in any way, including at corners." << std::endl
                  << "'&' - ship-cell, '—' - empty cell. If a cell is colored red, it means it has been already fired."
                  << std::endl;

        std::cout << *this << std::endl;
        askUserToPlaceShip(name, i);
        std::cout << "\033[2J\033[1;1H";
    }

    std::vector<Coordinates> userShipsCoords;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Board::Cell cell = player.getBoard().getCell(Coordinates(x, y));
            if (cell.getHasShip()) {
                userShipsCoords.emplace_back(x, y);
            }
        }
    }

    std::vector<Coordinates> computerShipsCoords;
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            Board::Cell cell = computer.getBoard().getCell(Coordinates(x, y));
            if (cell.getHasShip()) {
                computerShipsCoords.emplace_back(x, y);
            }
        }
    }

    while(!isGameOver) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << *this;
        userFire();
        computerFire();
        checkGameOver(computerShipsCoords, userShipsCoords);
    }

    if (isUserWinner) {
        std::cout << *this << std::endl;
        std::cout << "You have won! Congratulations!";
    } else {
        std::cout << *this << std::endl;
        std::cout << "Unfortunately, you have lost :( But try again!";
    }
}



