#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Pawn.h"
// TODO: Promotion mechanics, en passant

Pawn::Pawn(Color color, Field *field) : Piece(color, field) {
    this->moveDirection = (color == Color::WHITE) ? 1 : -1;
}

std::vector<Move> Pawn::getMoves() const {
    std::vector<Move> moves = {};

    // TODO: pins, checks?
    std::vector<Move> captures = attackingMoves();
    std::vector<Move> basicMoves = nonAttackingMoves();

    moves.insert(moves.end(), captures.begin(), captures.end());
    moves.insert(moves.end(), basicMoves.begin(), basicMoves.end());

    return moves;
}


PieceType Pawn::getType() const {
    return PieceType::PAWN;
}


char Pawn::getCharacter() const {
    return (color == Color::BLACK) ? 'p' : 'P';
}

std::string Pawn::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♟" : "♙";
}

bool Pawn::canMakeDoubleMove() const {
    if ((this->parentField->getPosition().getRow() == 2 && this->color == Color::WHITE) ||
        (this->parentField->getPosition().getRow() == 7 && this->color == Color::BLACK)) {
        return true;
    }
    return false;
}

std::vector<Move> Pawn::nonAttackingMoves() const {
    std::vector<Move> moves;
    auto singleMoveToPosition = parentField->getPosition().positionWithOffset(moveDirection, 0);
    bool possibleForwardMove = getBoard()->getField(singleMoveToPosition)->isEmpty();

    // Single forward push
    if (!possibleForwardMove) { return moves; }
    moves.emplace_back(parentField->getPosition(), singleMoveToPosition, (Piece *) this, false);

    // Double forward push
    if (canMakeDoubleMove()) {
        auto doubleMoveToPosition = parentField->getPosition().positionWithOffset(2 * moveDirection, 0);
        if (getBoard()->getField(doubleMoveToPosition)->isEmpty()) {
            moves.emplace_back(parentField->getPosition(), doubleMoveToPosition, (Piece *) this, false);
        }
    }
    return moves;
}

std::vector<Move> Pawn::attackingMoves() const {

    std::vector<Move> moves;

    // attack with a positive column offset
    if (possibleAttackInGivenDirection(true)) {
        auto toPosAfterAttack = parentField->getPosition().positionWithOffset(moveDirection, 1);
        moves.emplace_back(parentField->getPosition(), toPosAfterAttack, (Piece *) this, true);
    }

    if (possibleAttackInGivenDirection(false)) {
        auto toPosAfterAttack = parentField->getPosition().positionWithOffset(moveDirection, -1);
        moves.emplace_back(parentField->getPosition(), toPosAfterAttack, (Piece *) this, true);
    }
    return moves;
}

bool Pawn::possibleAttackInGivenDirection(bool positiveColumnOffset) const {
    int horizontalMoveDirection = (positiveColumnOffset) ? 1 : -1;
    auto position = this->getPosition();

    if (!position.offsetWithinBounds(moveDirection, horizontalMoveDirection)) {
        return false;
    }

    auto attackedPosition = position.positionWithOffset(moveDirection, horizontalMoveDirection);
    if (this->getBoard()->getField(attackedPosition)->isEmpty()) {
        return false;  // nothing to attack
    }

    return true;
}

