#include "Bishop.h"

Bishop::Bishop(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

std::vector<Move> Bishop::getMoves() const {
    return std::vector<Move>();
}

PieceType Bishop::getType() const {
    return PieceType::BISHOP;
}

Color Bishop::getColor() const {
    return color;
}

Board *Bishop::getBoard() const {
    return parentField->getBoard();
}

Field *Bishop::getField() const {
    return parentField;
}

Player *Bishop::getPlayer() const {
    return player;
}

char Bishop::getCharacter() const {
    return 'B';
}

std::string Bishop::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♝" : "♗";
}