#include "Piece.h"
#include "../Field.h"

Position Piece::getPosition() const {
    return this->getField()->getPosition();
}