#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H


#include <string>

class Position {
private:
    int column;
    int row;

public:
    Position(int row, int col);

    int getRow() const;

    int getCol() const;

    std::string toString() const;

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;

    bool offsetWithinBounds(int rowOffset, int colOffset) const;

    /**
     * Create a position with an offset relative to this
     * @throw std::invalid_argument if outside board boundary
     */
    Position positionWithOffset(int rowOffset, int colOffset) const;

    /**
     * Utility for constructing Position from standard notation eg. "e4" -> Position(4, 5)
     *
     * @param positionString standard notation of position - string of 1 character 1-h and 1 digit 1-8
     * @return equivalent position
     */
    static Position fromString(std::string positionString);

    static Position *copy(Position position);

    static bool withinBounds(int row, int col);
};


#endif //CHESS_POSITION_H
