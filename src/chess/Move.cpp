#include "Move.h"


const Position &Move::getFrom() const {
    return from;
}

const Position &Move::getTo() const {
    return to;
}

Piece *Move::getPiece() const {
    return piece;
}

bool Move::getIsCapture() const {
    return isCapture;
}

std::string Move::toString() const {
    std::stringstream ss;

    char pieceChar = piece->getCharacter();
    if (piece->getType() == PieceType::PAWN && isCapture) {
        pieceChar = 'a' + from.getCol() - 1;
    }

    ss << pieceChar;
    if (isCapture) {
        ss << 'x';
    }
    ss << to.toString();

    return ss.str();
}

