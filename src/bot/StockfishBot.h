#ifndef CHESS_STOCKFISHBOT_H
#define CHESS_STOCKFISHBOT_H


#include <QString>
#include "Game.h"

class StockfishBot {
private:
    const Game &game;

    static QString getStockfishOutput(const char *command);

    static QString getStockfishOutput(std::string fen);

    static std::string extractMove(QString stockfishOutput);

public:

    explicit StockfishBot(const Game &game) : game(game) {};

    Move getMoveFromStockfish(std::string gameFEN) const;
};


#endif //CHESS_STOCKFISHBOT_H
