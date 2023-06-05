#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <sstream>
#include "Position.h"
#include "pieces/PieceType.h"
#include "pieces/Piece.h"
#include "ChessExceptions.h"

class Position;

class Piece;

class Move {
private:
    Position from;
    Position to;
    Piece *movedPiece;
    Piece *capturedPiece;
    PieceType promoteTo;

public:
    Move(Position from, Position to, Piece *moved, Piece *captured, PieceType promoteTo) :
            from(from), to(to), movedPiece(moved), capturedPiece(captured), promoteTo(promoteTo) {
        validateMove();
    };

    Move(Position from, Position to, Piece *moved, Piece *captured) :
            from(from), to(to), movedPiece(moved), capturedPiece(captured), promoteTo(PieceType::NONE) {
        validateMove();
    };

    Move(Position from, Position to, Piece *moved) :
            from(from), to(to), movedPiece(moved), capturedPiece(nullptr), promoteTo(PieceType::NONE) {};

    Move(const Move &move) : from(move.getFrom()), to(move.getTo()), movedPiece(move.getPiece()),
                             capturedPiece(move.getCapturedPiece()), promoteTo(move.promoteTo) {
        validateMove();
    };

    Move(Position from, Position to, Piece *moved, PieceType promoteTo) :
            from(from), to(to), movedPiece(moved), capturedPiece(nullptr), promoteTo(promoteTo) {
        validateMove();
    };

    const Position &getFrom() const;

    const Position &getTo() const;

    Piece *getPiece() const;

    Piece *getCapturedPiece() const;

    bool isCapture() const;

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;

    void validateMove() const;

    std::string toString() const; //TODO - handle promotion-related stuff

    std::string toSmithNotation() const;

    bool isDoublePawnMove() const;

    bool isCastling() const;

    /**
     * Generates a rook move to complement the internal move representation of castling which only directly moves
     * the king.
     **/
    static Move generateCastlingComplement(Piece *CastlingRook);

    bool isLongCastle() const;

    bool resultsInPromotion() const;
};


#endif //CHESS_MOVE_H
