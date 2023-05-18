#include "King.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


King::King(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

std::vector<Move> King::getMoves() const {
    auto toPositions = getPossibleMovePositions();
    std::vector<Move> moves;

    for (auto toPos: toPositions) {
        if (getBoard()->getField(toPos)->isEmpty()) {
            moves.push_back(Move(getPosition(), toPos, (Piece *) this, false));
        } else if (getBoard()->getField(toPos)->getPiece()->getColor() != color) {
            moves.push_back(Move(getPosition(), toPos, (Piece *) this, true));
        }
    }
    return moves;
}

PieceType King::getType() const {
    return PieceType::KING;
}

Color King::getColor() const {
    return color;
}

Board *King::getBoard() const {
    return parentField->getBoard();
}

Field *King::getField() const {
    return parentField;
}

Player *King::getPlayer() const {
    return player;
}

char King::getCharacter() const {
    return (color == Color::BLACK) ? 'k' : 'K';
}

std::string King::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♚" : "♔";
}

std::vector<Position> King::getPossibleMovePositions() const {
    std::vector<std::pair<int, int>> offsets = {
            {-1, -1},
            {-1, 0},
            {-1, 1},
            {0,  -1},
            {0,  1},
            {1,  -1},
            {1,  0},
            {1,  1}
    };
    return getAllowedPositionsFromOffsets(offsets);
}
