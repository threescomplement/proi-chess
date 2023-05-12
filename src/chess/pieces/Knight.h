#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;

public:
    Knight(Color color, Field *field, Player *owner);

    ~Knight() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_KNIGHT_H
