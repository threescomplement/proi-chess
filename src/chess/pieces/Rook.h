#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "Piece.h"
#include "BasePiece.h"

class Rook : public BasePiece {
private:

public:
    using BasePiece::BasePiece;

    ~Rook() override;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Board *getBoard() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_ROOK_H
