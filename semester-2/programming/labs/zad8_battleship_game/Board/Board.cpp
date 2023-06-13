//
// Created by marling on 6/6/23.
//

#include "Board.hpp"

Board::Board() : board(10, std::vector<Cell>(10)) {};


Board::Cell& Board::getCell(const Coordinates& coordinate) {
    int row = coordinate.getRow();
    int col = coordinate.getColumn();
    return board[row][col];
}

std::string Board::checkIfPossibleToPlace(Coordinates& coord, int length) {
    int row = coord.getRow();
    int column = coord.getColumn();

    std::string possiblePosition; // none, vertical, horizontal, both

    bool vertical = true;
    bool horizontal = true;

    if((row > 9 || row < 0) || (column > 9 || column < 0) || board[row][column].getIsOccupied()) return "none";

    for (int i = 0; i < length; i++) {
        if(row - i < 0 && column + i > 9) return "none";
    }


    if (row + 1 - length >= 0) {
        for (int i = row; i > row - length; i--) {
            if (board[i][column].getIsOccupied()) {
                vertical = false;
                break;
            }
        }
    } else {
        vertical = false;
    }

    if (column - 1 + length <= 9) {
        for (int i = column; i < column + length; i++) {
            if (board[row][i].getIsOccupied()) {
                horizontal = false;
                break;
            }
        }
    } else {
        horizontal = false;
    }

    if (vertical && horizontal) return "both";

    return (vertical) ? "vertical" : "horizontal";
}

void Board::placeShip(std::vector<Coordinates>& coordinates) {
    for (const Coordinates &coordinate: coordinates) {
        int row = coordinate.getRow();
        int col = coordinate.getColumn();
        board[row][col].setHasShip();
    }
}

void Board::markCellsAsOccupied(Coordinates& coordinate) {
    int row = coordinate.getRow();
    int column = coordinate.getColumn();
    board[row][column].setIsOccupied();
    // add top shell
    if (row - 1 >= 0) {
        board[row - 1][column].setIsOccupied();
        // add top-left diagonal
        if (column - 1 >= 0) {
            board[row - 1][column - 1].setIsOccupied();
        }
        // add top-right diagonal
        if (column + 1 < 10) {
            board[row - 1][column + 1].setIsOccupied();
        }
    }
    // add bottom shell
    if (row + 1 < 10) {
        board[row + 1][column].setIsOccupied();
        // add bottom-left diagonal
        if (column - 1 >= 0) {
            board[row + 1][column - 1].setIsOccupied();
        }
        // add bottom-right diagonal
        if (column + 1 < 10) {
            board[row + 1][column + 1].setIsOccupied();
        }
    }
    // add left shell
    if (column - 1 >= 0) {
        board[row][column - 1].setIsOccupied();
    }
    // add right shell
    if (column + 1 < 10) {
        board[row][column + 1].setIsOccupied();
    }
}
