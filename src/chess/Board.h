#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#define BOARD_SIZE 8

#include <memory>
#include "Field.h"
#include "pieces/King.h"
#include "Move.h"

class Board {
private:
    Field fields[BOARD_SIZE][BOARD_SIZE];
    King *blackKing;
    King *whiteKing;

public:
    Board();
    void makeMove(Move move);
    Board afterMove(Move move) const;  // Deep copy
    std::string toStandardNotation() const;
};


#endif //CHESS_BOARD_H
