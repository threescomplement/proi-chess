#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <string>

#include "Piece.h"

enum class Color;
class Player;
class Field;
class Move;
enum class PieceType;
class Board;



class King : public Piece {
private:
    std::vector<Position> getPossibleMovePositions() const;

public:
    using Piece::Piece;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_KING_H
