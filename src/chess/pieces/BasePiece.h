#ifndef CHESS_BASEPIECE_H
#define CHESS_BASEPIECE_H

#include "Piece.h"

enum class Color;
class Field;

class BasePiece : public Piece {
protected:
    Color color;
    Field *parentField;

public:
    BasePiece(Color color, Field *field);

    Color getColor() const override;

    Field *getField() const override;

    void takeOffField() override;

};


#endif //CHESS_BASEPIECE_H
