//
// Created by mGarbowski on 27.04.2023.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H


#include <memory>
#include "pieces/Piece.h"
#include "Position.h"

class Field {
private:
    Piece *piece;
    Position position;

public:
    bool isEmpty() const;

    Piece *getPiece() const {
        return piece;
    }

    const Position &getPosition() const {
        return position;
    }
};


#endif //CHESS_FIELD_H
