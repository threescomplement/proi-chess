#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include <vector>
#include "Piece.h"

class Player {
public:
    Player();
    ~Player();
    bool isBot() const;
    std::vector<std::shared_ptr<Piece>>& getPieces();
private:
    std::vector<std::shared_ptr<Piece>> pieces;
    bool isPlayerBot;
};


#endif //CHESS_PLAYER_H
