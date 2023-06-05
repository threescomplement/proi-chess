#ifndef CHESS_CHESSBOT_H
#define CHESS_CHESSBOT_H

class Game;
class Move;

class ChessBot {
protected:
    const Game &game;
    int depth;
public:
    explicit ChessBot(const Game &game, int depth) : game(game), depth(depth) {};

    virtual ~ChessBot() = default;

    virtual Move getBestNextMove() const = 0;

    int getDepth() const;

    void setDepth(int depth);
};

#endif //CHESS_CHESSBOT_H
