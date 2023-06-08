/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "Piece.h"

class Knight : public Piece {
private:

    /**
     * Get all reachable positions on the board
     */
    std::vector<Position> getTargetPositions() const;

public:
    using Piece::Piece;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_KNIGHT_H
