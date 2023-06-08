/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "Knight.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


std::vector<Move> Knight::getMoves() const {
    std::vector<Move> moves;
    auto targetPositions = this->getTargetPositions();

    for (auto targetPosition: targetPositions) {
        auto targetField = this->getBoard()->getField(targetPosition);
        Piece *capturedPiece = nullptr;

        if (!targetField->isEmpty()) {
            auto targetPiece = targetField->getPiece();
            if (targetPiece->getColor() == this->getColor()) {
                continue;
            }

            capturedPiece = targetPiece;
        }

        moves.emplace_back(
                this->getField()->getPosition(),
                targetPosition,
                (Piece *) this,
                capturedPiece
        );
    }

    return moves;
}

PieceType Knight::getType() const {
    return PieceType::KNIGHT;
}


char Knight::getCharacter() const {
    return (color == Color::BLACK) ? 'n' : 'N';
}

std::string Knight::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♞" : "♘";
}

std::vector<Position> Knight::getTargetPositions() const {
    std::vector<Position> targetPositions;
    std::vector<std::pair<int, int>> offsets = {
            {-2, -1},
            {-1, -2},
            {1,  -2},
            {2,  -1},
            {2,  1},
            {1,  2},
            {-1, 2},
            {-2, 1}
    };

    return getAllowedPositionsFromOffsets(offsets);
}
