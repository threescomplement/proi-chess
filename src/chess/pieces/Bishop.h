#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"

class Bishop : public Piece {
private:

public:
    using Piece::Piece;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_BISHOP_H
