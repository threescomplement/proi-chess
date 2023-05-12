#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "Piece.h"

class Queen : public Piece {
private:
    Color color;
    Field *parentField;
    Player *player;

public:
    ~Queen() override;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_QUEEN_H
