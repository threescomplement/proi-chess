#include "Knight.h"
#include "PieceType.h"
#include "../Color.h"
#include "../Field.h"
#include <vector>


Knight::Knight(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
}

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

    for (auto offset: offsets) {
        try {
            targetPositions.push_back(
                    this->getField()
                            ->getPosition()
                            .positionWithOffset(offset.first, offset.second)
            );
        } catch (std::exception &e) {
            continue;  // Skip if position with offset is out of bounds
        }
    }

    return targetPositions;
}
