#ifndef CHESS_CHESSBOT_H
#define CHESS_CHESSBOT_H
class Game;
class Move;

class ChessBot {
protected:
    const Game &game;
public:
    explicit ChessBot(const Game &game): game(game) {};
    virtual ~ChessBot() = default;
    virtual Move getBestNextMove() const = 0;
};
#endif //CHESS_CHESSBOT_H
