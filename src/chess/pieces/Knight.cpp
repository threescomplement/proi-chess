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
        auto isCapture = false;

        if (!targetField->isEmpty()) {
            auto targetPieceColor = targetField->getPiece()->getColor();
            if (targetPieceColor == this->getColor()) {
                continue;
            }

            isCapture = true;
        }

        moves.emplace_back(
                this->getField()->getPosition(),
                targetPosition,
                (Piece *) this,
                isCapture
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
