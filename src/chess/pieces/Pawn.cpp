#include <vector>
#include "PieceType.h"
#include "../Color.h"
#include "../Board.h"
#include "Pawn.h"

Pawn::Pawn(Color color, Field *field, Player *owner) {
    this->color = color;
    this->parentField = field;
    this->player = owner;
    this->moveDirection = (color == Color::WHITE) ? 1 : -1;
}

std::vector<Move> Pawn::getMoves() const {
    std::vector<Move> moves = {};

    // TODO: 1. pins, checks

    // 2. if hasn't moved yet, can move one or two ranks up

    // 3. taking - is there a piece on the controlled field? if yes, what about the field behind it?


    // basic forward move - if no piece standing on the square

    return moves;
}


PieceType Pawn::getType() const {
    return PieceType::PAWN;
}


Color Pawn::getColor() const {
    return color;
}

Board *Pawn::getBoard() const {
    return parentField->getBoard();
}

Field *Pawn::getField() const {
    return parentField;
}

Player *Pawn::getPlayer() const {
    return player;
}

char Pawn::getCharacter() const {
    return 'P';
}

std::string Pawn::getUnicodeSymbol() const {
    return (color == Color::BLACK) ? "♟" : "♙";
}

bool Pawn::canMakeDoubleMove() const {
    /**
     * Returns the bool equal to !(has pawn moved yet) - whether it can perform a double move
     * */
    if ((this->parentField->getPosition().getRow() == 2 && this->color == Color::WHITE) ||
        (this->parentField->getPosition().getRow() == 7 && this->color == Color::BLACK))
        return false;
    return true;
}

std::vector<Move> Pawn::nonAttackingMoves() {
    /**
     * Returns a vector of possible non-attacking moves (max. two moves - single and double push).
     * Validates the board situation except checks and pins.
     * */
    std::vector<Move> moves;
    auto singleMoveToPosition = parentField->getPosition().positionWithOffset(moveDirection, 0);
    bool possibleForwardMove = getBoard()->getField(singleMoveToPosition)->isEmpty();

    // Single forward push
    if (!possibleForwardMove) {return moves;}
    moves.push_back(Move(parentField->getPosition(), singleMoveToPosition, this, false));

    // Double forward push
    if (canMakeDoubleMove()) {
        auto doubleMoveToPosition = parentField->getPosition().positionWithOffset(moveDirection, 0);
        if (getBoard()->getField(doubleMoveToPosition)->isEmpty()) {
            moves.push_back(Move(parentField->getPosition(), doubleMoveToPosition, this, false));
        }
    }
    return moves;
}

std::vector<Move> Pawn::attackingMoves() {
    std::vector<Move> moves;
    bool canMoveWithNegativeColumnOffset;
    bool canMoveWithPositiveColumnOffset;
    return {};
}


