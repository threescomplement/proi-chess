#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>

class Piece;

class Player {
private:
    std::string name;
    std::vector<Piece *> pieces;
    bool isChecked;
public:
    Player(std::string name);

    Player();

    ~Player();

    std::vector<Piece *> &getPieces();

};


#endif //CHESS_PLAYER_H
