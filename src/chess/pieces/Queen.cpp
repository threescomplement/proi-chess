#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Queen.h"

Queen::Queen(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

Queen::~Queen() = default;

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
    return (color == Color::BLACK) ? 'q' : 'Q';
}

std::string Queen::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♛" : "♕";
}
