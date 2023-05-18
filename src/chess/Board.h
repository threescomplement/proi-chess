#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <memory>
#include <utility>
#include "Field.h"
#include "Move.h"
#include "constants.h"
#include "pieces/Piece.h"

class Piece;

class Move;

class Field;

class Board {
private:
    std::array<std::array<Field *, BOARD_SIZE>, BOARD_SIZE> fields{};
    std::vector<Piece *> allPieces;
    Piece *blackKing;
    Piece *whiteKing;

public:
    Board();

    ~Board();

    void makeMove(Move move);

    Board afterMove(Move move) const;  // Deep copy
    std::string toStandardNotation() const;

    Field *getField(Position position) const;

    static Board *emptyBoard();

    /**
     * Create new board with all pieces set in their initial positions
     */
    static Board *startingBoard();

    std::string toString() const;

    std::string toFEN() const;

    /**
     * Creates a board object based on the given the FEN board description (without additional info, like castling
     * rights)
     */
    static Board *fromFEN(const std::string &FENDescription);
};

class IllegalMoveException : public std::exception {
private:
    std::string message;
public:
    explicit IllegalMoveException(std::string msg) : message(std::move(msg)) {}

    std::string what() {
        return message;
    }
};


#endif //CHESS_BOARD_H
