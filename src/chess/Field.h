//
// Created by mGarbowski on 27.04.2023.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H


#include <memory>
#include "pieces/Piece.h"
#include "Position.h"
#include "Board.h"

class Field {
private:
    Piece *piece;
    Position position;
    Board *parentBoard

public:
    bool isEmpty() const;

    Piece *getPiece() const {
        return piece;
    }

    const Position &getPosition() const {
        return position;
    }

    Board *getBoard() const;
};


#endif //CHESS_FIELD_H
