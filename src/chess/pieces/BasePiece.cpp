#include "BasePiece.h"

Color BasePiece::getColor() const {
    return color;
}

Field *BasePiece::getField() const {
    return parentField;
}

void BasePiece::takeOffField() {
    this->parentField = nullptr;
}

BasePiece::BasePiece(Color color, Field *field) {
    this->color = color;
    this->parentField = field;
}
