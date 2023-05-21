#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>

class Piece;


/**
 * Player is not responsible for freeing memory related to his Pieces
 */
class Player {
private:
    std::string name;
    std::vector<Piece *> pieces;
public:
    Player(std::string name);

    ~Player() = default;

    std::string const &getName() const;

    std::vector<Piece *> &getPieces();

};


#endif //CHESS_PLAYER_H
