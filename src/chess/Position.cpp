#include <sstream>
#include "Position.h"
#include "constants.h"

Position::Position(int row, int col) {
    if (row < 1 || row > BOARD_SIZE || col < 1 || col > BOARD_SIZE) {
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

Position Position::fromString(const std::string &pgn) {
    int row = std::stoi(std::string(1, pgn[1]));
    int col = pgn[0] - 'a' + 1;
    return {row, col};
}

