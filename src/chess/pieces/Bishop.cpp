/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "Bishop.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


std::vector<Move> Bishop::getMoves() const {
    return this->getMovesInDirections({{1,  1},
                                       {1,  -1},
                                       {-1, 1},
                                       {-1, -1}});
}

PieceType Bishop::getType() const {
    return PieceType::BISHOP;
}


char Bishop::getCharacter() const {
    return (color == Color::BLACK) ? 'b' : 'B';
}

std::string Bishop::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♝" : "♗";
}