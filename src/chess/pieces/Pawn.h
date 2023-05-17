
#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"


class Pawn : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;
    int moveDirection;

    /**
     * Returns the bool equal to !(has pawn moved yet) - whether it can perform a double move
     */
    bool canMakeDoubleMove() const;

    /**
     * Boolean indicating whether an attacking a controlled field is possible
     *
     * @param positiveColumnOffset - indicates in which horizontal direction to look for an attack in
     */
    bool possibleAttackInGivenDirection(bool positiveColumnOffset) const;

    /**
     * Returns a vector of possible non-attacking moves (max. two moves - single and double push).
     * Validates the board situation except checks and pins.
     */
    std::vector<Move> nonAttackingMoves() const;

    /**
     * Returns vector of possible attacking moves. Validates the board situation except checks and pins.
     */
    std::vector<Move> attackingMoves() const;


public:
    Pawn(Color color, Field *field, Player *owner);

    ~Pawn() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_PAWN_H
