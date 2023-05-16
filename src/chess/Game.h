#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <vector>

class Board;
class Move;
class Player;
class Piece;
class Position;
class King;

class Game {
private:
    Board  *board;
    Player *whitePlayer;
    Player *blackPlayer;
    Player *currentPlayer;
    King *whiteKing;
    King *blackKing;
    std::vector<Move> moveHistory;
    std::vector<Piece*> allPieces;

public:
    Game();

    ~Game();

    Board *getBoard();

    Player *getCurrentPlayer();

    std::vector<Move> &getMoveHistory();

    void makeMove(Move move);

    Game afterMove(Move move) const;

    std::vector<Move> getMovesFrom(Position position) const;

    std::vector<Move> getAllPlayerMoves(Player &player) const;

    bool isMate() const;

    bool isCheck() const;


};


#endif //CHESS_GAME_H
