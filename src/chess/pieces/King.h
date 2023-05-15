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
    Color color;
    Field *parentField;
    Player *player;

public:
    King(Color color, Field *field, Player *owner);

    ~King() override = default;

    std::vector<Move> getMoves() const override;

    PieceType getType() const override;

    Color getColor() const override;

    Board *getBoard() const override;

    Field *getField() const override;

    Player *getPlayer() const override;

    char getCharacter() const override;

    std::string getUnicodeSymbol() const override;
};


#endif //CHESS_KING_H
