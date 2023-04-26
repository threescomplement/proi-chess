#ifndef CHESS_MATCH_H
#define CHESS_MATCH_H


#include <vector>
#include "Board.h"
#include "Move.h"
#include "Player.h"

class Match {
public:
    Match();
    Player getCurrentPlayer() const;
    void makeMove();
    void initializeMatch();
private:
    Board board;
    std::vector<Move> moveHistory;
    Player whitePlayer;
    Player blackPlayer;
};


#endif //CHESS_MATCH_H
