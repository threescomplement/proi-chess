#include "Knight.h"

Knight::Knight(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

std::vector<Move> Knight::getMoves() const {
    return std::vector<Move>();
}

PieceType Knight::getType() const {
    return PieceType::KNIGHT;
}

Color Knight::getColor() const {
    return color;
}

Board *Knight::getBoard() const {
    return parentField->getBoard();
}

Field *Knight::getField() const {
    return parentField;
}

Player *Knight::getPlayer() const {
    return player;
}

char Knight::getCharacter() const {
    return 'N';
}

std::string Knight::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♞" : "♘";
}