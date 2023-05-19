#include "King.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


std::vector<Move> King::getMoves() const {
    auto toPositions = getPossibleMovePositions();
    std::vector<Move> moves;

    for (auto toPos: toPositions) {
        if (getBoard()->getField(toPos)->isEmpty()) {
            moves.emplace_back(getPosition(), toPos, (Piece *) this);
        } else if (getBoard()->getField(toPos)->getPiece()->getColor() != color) {
            moves.emplace_back(getPosition(), toPos, (Piece *) this, getBoard()->getField(toPos)->getPiece());
        }
    }
    return moves;
}

PieceType King::getType() const {
    return PieceType::KING;
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
