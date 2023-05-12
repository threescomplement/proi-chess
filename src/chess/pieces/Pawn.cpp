#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Pawn.h"

Pawn::Pawn(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

Pawn::~Pawn() = default;

std::vector <Move> Pawn::getMoves() const {
    return std::vector<Move>();
}

PieceType Pawn::getType() const {
    return PieceType::PAWN;
}

Color Pawn::getColor() const {
    return color;
}

Board *Pawn::getBoard() const {
    return parentField->getBoard();
}

Field *Pawn::getField() const {
    return parentField;
}

Player *Pawn::getPlayer() const {
    return player;
}

char Pawn::getCharacter() const {
    return 'P';
}

std::string Pawn::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♟" : "♙";
}
