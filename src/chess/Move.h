#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <sstream>
#include "Position.h"
#include "pieces/Piece.h"

class Position;
class Piece;

class Move {
private:
    Position from;
    Position to;
    Piece *piece;
    bool isCapture;

public:
    Move(Position from, Position to, Piece *piece, bool isCaputre) :
            from(from), to(to), piece(piece), isCapture(isCaputre) {};

    const Position &getFrom() const;

    const Position &getTo() const;

    Piece *getPiece() const;

    bool getIsCapture() const;

    bool operator==(const Move& rhs) const;

    bool operator!=(const Move& rhs) const;

    std::string toString() const;
};


#endif //CHESS_MOVE_H
