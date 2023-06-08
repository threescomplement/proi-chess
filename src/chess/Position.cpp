/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include <sstream>
#include "Position.h"
#include "constants.h"

Position::Position(int row, int col) {
    if (!Position::withinBounds(row, col)) {
        throw std::invalid_argument("Invalid coordinates");
    }

    this->row = row;
    this->column = col;
}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return column;
}

std::string Position::toString() const {
    char rowChar = '0' + row;
    char colChar = 'a' + column - 1;
    std::stringstream ss;
    ss << colChar << rowChar;
    return ss.str();
}

bool Position::operator==(const Position &rhs) const {
    return column == rhs.column && row == rhs.row;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

Position Position::positionWithOffset(int rowOffset, int colOffset) const {
    return {getRow() + rowOffset, getCol() + colOffset};


}


Position Position::fromString(std::string positionString) {
    if (positionString.size() != 2) {
        throw std::invalid_argument("Invalid representation of a position");
    }

    auto col = positionString[0];
    auto row = positionString[1];
    auto colNumeric = col - 'a' + 1;
    auto rowNumeric = row - '0';
    return {rowNumeric, colNumeric};
}

bool Position::withinBounds(int row, int col) {
    if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE) {
        return false;
    }

    return true;
}

bool Position::offsetWithinBounds(int rowOffset, int colOffset) const {
    return Position::withinBounds(this->getRow() + rowOffset, this->getCol() + colOffset);
}

Position *Position::copy(Position position) {
    return new Position(position.getRow(), position.getCol());
}

