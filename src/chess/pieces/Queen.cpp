#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Queen.h"

Queen::~Queen() = default;

std::vector <Move> Queen::getMoves() const {
    return std::vector<Move>();
}

PieceType Queen::getType() const {
    return PieceType::QUEEN;
}

Color Queen::getColor() const {
    return color;
}

Board *Queen::getBoard() const {
    return parentField->getBoard();
}

Field *Queen::getField() const {
    return parentField;
}

Player *Queen::getPlayer() const {
    return player;
}

char Queen::getCharacter() const {
    return 'Q';
}

std::string Queen::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♛" : "♕";
}
