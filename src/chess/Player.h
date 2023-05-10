#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include <vector>
#include "pieces/Piece.h"

class Player {
private:
    std::string name;
    std::vector<Piece *> pieces;
    bool isChecked;
public:
    Player();
    ~Player();
    std::vector<Piece *> &getPieces() const;

};


#endif //CHESS_PLAYER_H
