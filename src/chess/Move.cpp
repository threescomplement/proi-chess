/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "Move.h"
#include "pieces/PieceType.h"
#include "Game.h"
#include "Player.h"
#include "pieces/Pawn.h"

std::map<std::string, PieceType> Move::promotionMapping = {
        {" ", PieceType::NONE},
        {"q", PieceType::QUEEN},
        {"b", PieceType::BISHOP},
        {"r", PieceType::ROOK},
        {"n", PieceType::KNIGHT},
};

std::map<PieceType, std::string> Move::reversePromotionMapping = {
        {PieceType::QUEEN,  "q"},
        {PieceType::BISHOP, "b"},
        {PieceType::ROOK,   "r"},
        {PieceType::KNIGHT, "n"},
};

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
    if (this->resultsInPromotion()) {
        ss << Move::reversePromotionMapping[this->getPromoteTo()];
    }
    return ss.str();
}

bool Move::isCastling() const {
    if (movedPiece->getType() == PieceType::KING && abs(getTo().getCol() - getFrom().getCol()) == 2)
        return true;
    return false;
}

Move Move::generateCastlingComplement(Piece *castlingRook, bool forReversal = false) {
    int row = castlingRook->getPosition().getRow();
    if (forReversal) {
        int fromCol = (castlingRook->getPosition().getCol() == 4) ? 1 : 8;
        return Move(Position(row, fromCol), castlingRook->getPosition(), castlingRook, nullptr);
    } else {
        int toCol = (castlingRook->getPosition().getCol() == 1) ? 4 : 6;
        return Move(castlingRook->getPosition(), Position(row, toCol), castlingRook, nullptr);
    }
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

Move Move::parseSmithNotation(const std::string &moveStr, const Game &game) {
    if (moveStr.size() != 4 && moveStr.size() != 5) {
        throw IllegalMoveException("Invalid representation of a move");
    }

    auto promotionType = (moveStr.size() == 5)
                         ? Move::promotionMapping[moveStr.substr(4, 1)]
                         : PieceType::NONE;

    Position sourcePosition = Position::fromString(moveStr.substr(0, 2));
    Position targetPosition = Position::fromString(moveStr.substr(2, 2));
    return Move::fromPositions(game, sourcePosition, targetPosition, promotionType);
}


Move Move::fromPositions(const Game &game, Position from, Position to, PieceType promotion) {
    auto enPassantTargetPos = game.getEnPassantTargetPosition();
    auto movedPiece = game.getPiece(from);
    auto capturedPiece = (enPassantTargetPos != nullptr && (*enPassantTargetPos) == to)
                         ? dynamic_cast<Piece *>(game.getEnPassantTargetPiece())
                         : game.getPiece(to);

    if (movedPiece == nullptr) {
        throw IllegalMoveException("Cannot move from empty field");
    }

    return {from, to, movedPiece, capturedPiece, promotion};
}

