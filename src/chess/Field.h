/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H


#include <memory>
#include "pieces/Piece.h"
#include "Position.h"
#include "Board.h"

class Board;
class Piece;

class Field {
private:
    Piece *piece;
    Position position;
    Board *parentBoard;

public:
    explicit Field(Position position): piece(nullptr), position(position), parentBoard(nullptr) {};

    Field(Piece *piece, Position position, Board *parentBoard) :
            piece(piece), position(position), parentBoard(parentBoard) {};

    ~Field() = default;

    const Position &getPosition() const;

    Piece *getPiece() const;

    void setPiece(Piece *newPiece);

    Board *getBoard() const;

    bool isEmpty() const;
};


#endif //CHESS_FIELD_H
