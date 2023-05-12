#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;

public:
    ~Rook() override;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_ROOK_H
