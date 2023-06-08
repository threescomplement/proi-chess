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
#include "Queen.h"


std::vector<Move> Queen::getMoves() const {
    return this->getMovesInDirections({{1,  0},
                                       {-1, 0},
                                       {0,  1},
                                       {0,  -1},
                                       {1,  1},
                                       {1,  -1},
                                       {-1, 1},
                                       {-1, -1}});
}

PieceType Queen::getType() const {
    return PieceType::QUEEN;
}


char Queen::getCharacter() const {
    return (color == Color::BLACK) ? 'q' : 'Q';
}

std::string Queen::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♛" : "♕";
}
