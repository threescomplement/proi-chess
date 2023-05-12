#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <memory>
#include "Field.h"
#include "Move.h"
#include "constants.h"
#include "pieces/Piece.h"
class Piece;
class Move;

class Board {
private:
    Field fields[BOARD_SIZE][BOARD_SIZE];
    Piece *blackKing;
    Piece *whiteKing;

public:
    Board();
    void makeMove(Move move);
    Board afterMove(Move move) const;  // Deep copy
    std::string toStandardNotation() const;
};


#endif //CHESS_BOARD_H
