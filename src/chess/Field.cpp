#include "Field.h"

Piece *Field::getPiece() const {
    return piece;
}

const Position &Field::getPosition() const {
    return position;
}

bool Field::isEmpty() const {
    return (piece == nullptr);
}

Board *Field::getBoard() const {
    return parentBoard;
}

