#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <sstream>
#include "Position.h"
#include "pieces/Piece.h"

class Position;
class Game;
class Piece;

class Move {
private:
    Position from;
    Position to;
    Piece *movedPiece;
    Piece *capturedPiece;

public:
    Move(Position from, Position to, Piece *moved, Piece *captured) :
            from(from), to(to), movedPiece(moved), capturedPiece(captured) {};

    Move(Position from, Position to, Piece *moved) :
            from(from), to(to), movedPiece(moved), capturedPiece(nullptr) {};

    Move(const Move &move): from(move.getFrom()), to(move.getTo()), movedPiece(move.getPiece()), capturedPiece(move.getCapturedPiece()){};


    const Position &getFrom() const;

    const Position &getTo() const;

    Piece *getPiece() const;

    Piece *getCapturedPiece() const;

    bool isCapture() const;

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;

    std::string toString() const;

    std::string toStockfishNotation() const; // TODO: rename

    bool isDoublePawnMove() const;

    bool isCastling() const;

    /**
     * Generates a rook move to complement the internal move representation of castling which only directly moves
     * the king.
     **/
    static Move generateCastlingComplement(Piece *CastlingRook);

    static Move parseStockfishNotation(const std::string &moveStr, const Game &game);

    bool isLongCastle() const;
};


#endif //CHESS_MOVE_H
