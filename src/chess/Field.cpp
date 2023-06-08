/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

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

void Field::setPiece(Piece *newPiece) {
    this->piece = newPiece;
}
