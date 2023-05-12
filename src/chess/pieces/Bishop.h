#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"

class Bishop : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;

public:
    Bishop(Color color, Field *field, Player *owner);

    ~Bishop() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_BISHOP_H
