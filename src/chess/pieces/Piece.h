#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include <vector>
#include <string>

enum class Color;

class Move;

class Board;

class Player;

class Field;

enum class PieceType;

class Position;

class Move;

class Piece {
private:
    /**
     * Get moves in a straight line until another movedPiece or edge of the board is reached
     * arguments define the direction of the line
     * @param rowDirection - {-1, 0, 1}
     * @param colDirection - {-1, 0, 1}
     */
    virtual std::vector<Move> getMovesInDirection(int rowDirection, int colDirection) const;

protected:

    Color color;
    Field *parentField;
    /**
     * Return moves in straight lines, stopping at board boundary, friendly movedPiece or a capture
     * in all of the given directions.
     *
     * Directions must have values from {-1, 0, 1}, eg. {1, -1} -> diagonally to upper-left
     *
     * @param directions vector of pairs {rowDirection, colDirection}
     */
    virtual std::vector<Move> getMovesInDirections(std::vector<std::pair<int, int>> const &directions) const;

public:
    Piece(Color color, Field *field);

    virtual ~Piece() = default;

    virtual std::vector<Move> getMoves() const = 0;

    virtual PieceType getType() const = 0;

    virtual Color getColor() const;

    virtual Board *getBoard() const;

    virtual Field *getField() const;

    virtual void setField(Field *newField);

    virtual char getCharacter() const = 0;

    virtual Position getPosition() const;

    virtual std::string getUnicodeSymbol() const = 0;

    virtual void takeOffField();

    virtual std::vector<Position> getAllowedPositionsFromOffsets(const std::vector<std::pair<int, int>> &offsets) const;
};


#endif //CHESS_PIECE_H
