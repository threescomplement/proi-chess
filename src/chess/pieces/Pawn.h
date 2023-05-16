
#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"


class Pawn : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;
    bool canMakeDoubleMove() const;
    std::vector<Move> nonAttackingMoves();
    std::vector<Move> attackingMoves();
    int moveDirection;


public:
    Pawn(Color color, Field *field, Player *owner);

    ~Pawn() override=default;

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
