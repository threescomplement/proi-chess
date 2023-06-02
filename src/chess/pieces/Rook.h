#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"

class Rook : public Piece {
private:

public:
    using Piece::Piece;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_ROOK_H
