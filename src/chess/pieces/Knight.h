#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"
#include "BasePiece.h"

class Knight : public BasePiece {
private:

    /**
     * Get all reachable positions on the board
     */
    std::vector<Position> getTargetPositions() const;

public:
    using BasePiece::BasePiece;

    ~Knight() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Board *getBoard() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_KNIGHT_H
