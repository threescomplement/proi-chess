
#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Rook.h"


Rook::~Rook() = default;

std::vector<Move> Rook::getMoves() const {
    return this->getMovesInDirections({{1,  0},
                                       {-1, 0},
                                       {0,  1},
                                       {0,  -1}});
}

PieceType Rook::getType() const {
    return PieceType::ROOK;
}

Board *Rook::getBoard() const {
    return parentField->getBoard();
}

char Rook::getCharacter() const {
    return (color == Color::BLACK) ? 'r' : 'R';
}

std::string Rook::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♜" : "♖";
}
