#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Move.h"
#include "../Board.h"
#include "../Player.h"

class Move;

class Piece {
public:
    virtual ~Piece() = 0;
    virtual std::vector<Move> getMoves() const = 0;
    virtual PieceType getType() const = 0;
    virtual Color getColor() const = 0;
    virtual Board *getBoard() const = 0;
    virtual Field *getField() const = 0;
    virtual Player *getPlayer() const = 0;
    virtual char getCharacter() const = 0;
    virtual std::string getUnicodeSymbol() const = 0;
};


#endif //CHESS_PIECE_H
