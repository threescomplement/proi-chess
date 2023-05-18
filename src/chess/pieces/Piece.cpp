#include "Piece.h"
#include "../Field.h"

Position Piece::getPosition() const {
    return this->getField()->getPosition();
}

std::vector<Move> Piece::getMovesInDirection(int rowDirection, int colDirection) const {
    if (rowDirection != -1 && rowDirection != 0 && rowDirection != 1) {
        throw std::invalid_argument("Directions must be values from {-1, 0, 1}");
    }
    if (colDirection != -1 && colDirection != 0 && colDirection != 1) {
        throw std::invalid_argument("Directions must be values from {-1, 0, 1}");
    }
    if (rowDirection == 0 && colDirection == 0) {
        throw std::invalid_argument("Direction cannot be (0,0)");
    }

    std::vector<Move> moves;
    auto sourcePosition = this->getPosition();
    auto rowOffset = rowDirection;
    auto colOffset = colDirection;

    while (Position::withinBounds(sourcePosition.getRow() + rowOffset, sourcePosition.getCol() + colOffset)) {
        auto targetPosition = sourcePosition.positionWithOffset(rowOffset, colOffset);
        auto targetField = this->getBoard()->getField(targetPosition);

        if (!targetField->isEmpty()) {
            if (targetField->getPiece()->getColor() != this->getColor()) {  // Is capture
                moves.emplace_back(sourcePosition, targetPosition, (Piece *) this, true);
            }
            break;  // Reached either capture or friendly piece
        }

        moves.emplace_back(
                sourcePosition,
                targetPosition,
                (Piece *) this,
                false
        );

        rowOffset += rowDirection;
        colOffset += colDirection;
    }

    return moves;
}

std::vector<Move> Piece::getMovesInDirections(std::vector<std::pair<int, int>> const &directions) const {
    std::vector<Move> moves;
    for (auto const &direction: directions) {
        auto movesInDirection = this->getMovesInDirection(direction.first, direction.second);
        moves.insert(moves.end(), movesInDirection.begin(), movesInDirection.end());
    }

    return moves;
}

std::vector<Position> Piece::getAllowedPositionsFromOffsets(const std::vector<std::pair<int, int>> &offsets) const {
    std::vector<Position> targetPositions;

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
