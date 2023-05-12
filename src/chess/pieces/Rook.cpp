
#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Rook.h"

Rook::~Rook() = default;

std::vector <Move> Rook::getMoves() const {
    return std::vector<Move>();
}

PieceType Rook::getType() const {
    return PieceType::ROOK;
}

Color Rook::getColor() const {
    return color;
}

Board *Rook::getBoard() const {
    return parentField->getBoard();
}

Field *Rook::getField() const {
    return parentField;
}

Player *Rook::getPlayer() const {
    return player;
}

char Rook::getCharacter() const {
    return 'R';
}

std::string Rook::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♜" : "♖";
}
