#include "Move.h"
#include "pieces/PieceType.h"

const Position &Move::getFrom() const {
    return from;
}

const Position &Move::getTo() const {
    return to;
}

Piece *Move::getPiece() const {
    return movedPiece;
}

bool Move::isCapture() const {
    return (capturedPiece != nullptr);
}

std::string Move::toString() const {
    std::stringstream ss;

    char pieceChar;
    if (movedPiece->getType() == PieceType::PAWN) {
        pieceChar = (this->isCapture()) ? 'a' + from.getCol() - 1 : '\0';
    } else { pieceChar = movedPiece->getCharacter(); }

    if (pieceChar) { ss << pieceChar; }
    if (this->isCapture()) {
        ss << 'x';
    }
    ss << to.toString();

    return ss.str();
}

bool Move::operator==(const Move &rhs) const {
    return (
            from == rhs.from &&
            to == rhs.to &&
            movedPiece == rhs.movedPiece &&
            capturedPiece == rhs.capturedPiece
    );
}

bool Move::operator!=(const Move &rhs) const {
    return !((*this) == rhs);
}

Piece *Move::getCapturedPiece() const {
    return capturedPiece;
}

bool Move::isDoublePawnMove() const {
    auto sourceRow = this->getFrom().getRow();
    auto targetRow = this->getTo().getRow();
    auto type = this->getPiece()->getType();
    return (type == PieceType::PAWN && abs(sourceRow - targetRow) == 2);
}

