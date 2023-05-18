#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "Piece.h"
#include "BasePiece.h"

class Bishop : public BasePiece {
private:

public:
    using BasePiece::BasePiece;

    ~Bishop() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Board *getBoard() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_BISHOP_H
