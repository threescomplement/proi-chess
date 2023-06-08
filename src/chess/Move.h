/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include <sstream>
#include <map>
#include "Position.h"
#include "pieces/PieceType.h"
#include "pieces/Piece.h"
#include "ChessExceptions.h"

class Position;
class Game;
class Piece;

class Move {
private:
    Position from;
    Position to;
    Piece *movedPiece;
    Piece *capturedPiece;
    PieceType promoteTo;

    static std::map<std::string, PieceType> promotionMapping;

    static std::map<PieceType, std::string> reversePromotionMapping;

    void validateMove() const;

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

    PieceType getPromoteTo() const;

    bool isCapture() const;

    bool operator==(const Move &rhs) const;

    bool operator!=(const Move &rhs) const;

    std::string toString() const; //TODO - handle promotion-related stuff

    std::string toSmithNotation() const;

    bool isDoublePawnMove() const;

    bool isCastling() const;

    /**
     * Generates a rook move to complement the internal move representation of castling which only directly moves
     * the king.
     **/
    static Move generateCastlingComplement(Piece *CastlingRook);

    static Move parseSmithNotation(const std::string &moveStr, const Game &game);

    static Move fromPositions(const Game &game, Position from, Position to, PieceType promotion = PieceType::NONE);

    bool isLongCastle() const;

    bool resultsInPromotion() const;

    void setPromotion(PieceType promoteTo);
};


#endif //CHESS_MOVE_H
