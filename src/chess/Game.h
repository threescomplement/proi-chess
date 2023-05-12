#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <vector>
#include "Board.h"
#include "Move.h"
#include "Player.h"

class Game {
private:
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    Player &currentPlayer;
    std::vector<Move> moveHistory;
    std::vector<Piece*> allPieces;

public:
    Game();

    ~Game();

    Board &getBoard();

    Player &getCurrentPlayer() const;

    void makeMove(Move move);

    Game afterMove(Move move) const;

    std::vector<Move> getMovesFrom(Position position) const;

    std::vector<Move> getAllPlayerMoves(Player &player) const;

    bool isMate() const;

    bool isCheck() const;
};


#endif //CHESS_GAME_H
