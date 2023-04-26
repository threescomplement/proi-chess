#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#define BOARD_SIZE 8

#include <memory>
#include "Field.h"
#include "pieces/King.h"
#include "Move.h"

class Board {
public:
    Board();
    void makeMove(Move move);
    Board afterMove(Move move) const;
    std::string toStandardNotation() const;

private:
    Field fields[BOARD_SIZE][BOARD_SIZE];
    std::shared_ptr<King> blackKing;
    std::shared_ptr<King> whiteKing;

    bool isCheck() const;
    bool isMate() const;
};


#endif //CHESS_BOARD_H
