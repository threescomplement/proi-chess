#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include <vector>
//#include "PieceType.h"
//#include "../Color.h"
//#include "../Move.h"
//#include "../Board.h"
//#include "../Player.h"

#include <string>

enum class Color;
class Move;
class Board;
class Player;
class Field;
enum class PieceType;


class Move;

class Piece {
public:
    virtual ~Piece() = default;

    virtual std::vector<Move> getMoves() const = 0;

    virtual PieceType getType() const = 0;

    virtual Color getColor() const = 0;

    virtual Board *getBoard() const = 0;

    virtual Field *getField() const = 0;

    virtual Player *getPlayer() const = 0;

    virtual char getCharacter() const = 0;

    virtual std::string getUnicodeSymbol() const = 0;
};


#endif //CHESS_PIECE_H
