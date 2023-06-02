#ifndef CHESS_STOCKFISHBOT_H
#define CHESS_STOCKFISHBOT_H


#include <QString>
#include "Game.h"

/**
 * Requires stockfish to be installed and on the system PATH
 */
class StockfishBot {
private:
    const Game &game;

    Move getMoveFromStockfish(std::string gameFEN) const;

    static const std::string stockfishProgramName;

    static QString getStockfishOutput(const char *command);

    static QString getStockfishOutput(std::string fen);

    static std::string extractMove(QString stockfishOutput);

public:

    explicit StockfishBot(const Game &game) : game(game) {};

    Move getBestNextMove() const;
};


#endif //CHESS_STOCKFISHBOT_H
