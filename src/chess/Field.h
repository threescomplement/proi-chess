//
// Created by mGarbowski on 27.04.2023.
//

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H


#include <memory>
#include "Piece.h"
#include "Position.h"

class Field {
public:
    bool isEmpty() const;
private:
    std::shared_ptr<Piece> piece;
    Position position;
};


#endif //CHESS_FIELD_H
