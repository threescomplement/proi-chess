#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <memory>
#include "Field.h"
#include "Move.h"
#include "constants.h"
#include "pieces/Piece.h"

class Piece;

class Move;

class Field;

class Board {
private:
    std::array<std::array<Field *, BOARD_SIZE>, BOARD_SIZE> fields;
    Piece *blackKing;
    Piece *whiteKing;

public:
    Board();

    void makeMove(Move move);

    Board afterMove(Move move) const;  // Deep copy
    std::string toStandardNotation() const;

    Field *getField(Position position) const;

    void setBlackKing(Piece *blackKing);

    void setWhiteKing(Piece *whiteKing);

    static Board* emptyBoard();

    std::string toString() const;

    std::string toFEN() const;

    static Board* fromFEN(const std::string& FENDescription);
};


#endif //CHESS_BOARD_H
