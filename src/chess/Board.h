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

    void makeMove(const Move &move);

    void reverseMove(const Move &move, bool isEnPassant=false);

    void executePromotion(const Move &move);

    Field *getField(Position position) const;

    Piece *getBlackKing() const;

    Piece *getWhiteKing() const;

    void setBlackKing(Piece *blackKing);

    void setWhiteKing(Piece *whiteKing);

    std::vector<Piece *> &getAllPieces();

    static Board *emptyBoard();

    /**
     * Create new board with all pieces set in their initial positions
     */
    static Board *startingBoard();

    std::string toString() const;
};


#endif //CHESS_BOARD_H
