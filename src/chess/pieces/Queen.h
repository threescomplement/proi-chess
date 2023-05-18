#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "BasePiece.h"

class Piece;

class Queen : public BasePiece {
private:

public:
    using BasePiece::BasePiece;

    ~Queen() override;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Board *getBoard() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_QUEEN_H
