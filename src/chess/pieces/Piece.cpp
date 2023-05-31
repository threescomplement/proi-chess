#include "Piece.h"
#include "../Field.h"
#include "../ChessExceptions.h"

Position Piece::getPosition() const {
    if (this->getField() == nullptr) {
        throw PieceNotOnBoardException(
                "Cannot access position as piece is not currently bound to any field on the board"
        );
    }
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

    while (sourcePosition.offsetWithinBounds(rowOffset, colOffset)) {
        auto targetPosition = sourcePosition.positionWithOffset(rowOffset, colOffset);
        auto targetField = this->getBoard()->getField(targetPosition);

        if (!targetField->isEmpty()) {
            auto otherPiece = targetField->getPiece();
            if (otherPiece->getColor() != this->getColor()) {  // Is capture
                moves.emplace_back(sourcePosition, targetPosition, (Piece *) this, otherPiece);
            }
            break;  // Reached either capture or friendly piece
        }

        moves.emplace_back(
                sourcePosition,
                targetPosition,
                (Piece *) this
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
    auto sourcePosition = this->getPosition();

    for (auto offset: offsets) {
        if (sourcePosition.offsetWithinBounds(offset.first, offset.second)) {
            targetPositions.push_back(sourcePosition.positionWithOffset(offset.first, offset.second));
        }
    }
    return targetPositions;
}


Color Piece::getColor() const {
    return color;
}

Field *Piece::getField() const {
    return parentField;
}

void Piece::takeOffField() {
    this->parentField = nullptr;
}

Piece::Piece(Color color, Field *field) {
    this->color = color;
    this->parentField = field;
}

Board *Piece::getBoard() const {
    return this->parentField->getBoard();
}

void Piece::setField(Field *newField) {
    this->parentField = newField;
}
