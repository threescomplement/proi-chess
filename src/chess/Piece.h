#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include <vector>
#include "PieceType.h"
#include "Color.h"
#include "Move.h"
#include "Board.h"

class Piece {
public:
    virtual ~Piece() = 0;
    virtual std::vector<Move> getLegalMoves(Board &board) const = 0;
    virtual PieceType getType() const = 0;
    virtual Color getColor() const = 0;
};


#endif //CHESS_PIECE_H
