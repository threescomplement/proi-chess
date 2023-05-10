#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "pieces/Piece.h"

class Move {
private:
    const Position from;
    const Position to;
    Piece *piece;
    const bool isAttack;

public:
    const Position &getFrom() const {
        return from;
    }

    const Position &getTo() const {
        return to;
    }

    Piece *getPiece() const {
        return piece;
    }

    const bool getIsAttack() const {
        return isAttack;
    }
};


#endif //CHESS_MOVE_H
