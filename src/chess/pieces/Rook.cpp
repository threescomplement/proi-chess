/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Rook.h"


std::vector<Move> Rook::getMoves() const {
    return this->getMovesInDirections({{1,  0},
                                       {-1, 0},
                                       {0,  1},
                                       {0,  -1}});
}

PieceType Rook::getType() const {
    return PieceType::ROOK;
}


char Rook::getCharacter() const {
    return (color == Color::BLACK) ? 'r' : 'R';
}

std::string Rook::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♜" : "♖";
}
