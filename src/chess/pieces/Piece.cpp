#include "Piece.h"
#include "../Field.h"

Position Piece::getPosition() const {
    return this->getField()->getPosition();
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
