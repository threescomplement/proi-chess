#include "Move.h"
#include "pieces/PieceType.h"
#include "pieces/Pawn.h"

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
    if (isCastling()) {
        if (getTo().getCol() == 3)
            return "O-O-O";
        return "O-O";
    }

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

std::string Move::toSmithNotation() const {
    std::stringstream ss;
    ss << this->getFrom().toString() << this->getTo().toString();
    return ss.str();
}

bool Move::isCastling() const {
    if (movedPiece->getType() == PieceType::KING && abs(getTo().getCol() - getFrom().getCol()) == 2)
        return true;
    return false;
}

Move Move::generateCastlingComplement(Piece *castlingRook) {
    int toCol = (castlingRook->getPosition().getCol() == 1) ? 4 : 6;
    int row = castlingRook->getPosition().getRow();
    return Move(castlingRook->getPosition(), Position(row, toCol), castlingRook, nullptr);
}

bool Move::isLongCastle() const {
    return (isCastling() && getTo().getCol() == 3);
}

bool Move::resultsInPromotion() const {
    if (getPiece()->getType() != PieceType::PAWN)
        return false;
    // if a pawn moves "up", it promotes on rank 8, else on rank 1
    int promotionRankForThisPawn = (dynamic_cast<Pawn *>(getPiece())->getMoveDirection() == 1) ? 8 : 1;
    return getTo().getRow() == promotionRankForThisPawn;
}

void Move::validateMove() const {
    if (movedPiece->getType() != PieceType::PAWN && promoteTo != PieceType::NONE)
        throw IllegalMoveException("Non-pawn pieces cannot promote!");
    if (promoteTo != PieceType::NONE && !resultsInPromotion())
        throw IllegalMoveException("Pawn not eligible for promotion!");
}

PieceType Move::getPromoteTo() const {
    return promoteTo;
}

void Move::setPromotion(PieceType type) {
    this->promoteTo = type;
}

