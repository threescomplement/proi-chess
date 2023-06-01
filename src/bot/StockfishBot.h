#ifndef CHESS_STOCKFISHBOT_H
#define CHESS_STOCKFISHBOT_H


#include <QString>
#include "Game.h"
#include "ChessBot.h"

/**
 * Requires stockfish to be installed and on the system PATH
 */
class StockfishBot : public ChessBot {
private:
    Move getMoveFromStockfish(std::string gameFEN) const;

    static const std::string stockfishProgramName;

    static QString getStockfishOutput(const char *command);

    static QString getStockfishOutput(std::string fen);

    static std::string extractMove(QString stockfishOutput);

public:
    using ChessBot::ChessBot;

    Move getBestNextMove() const override;
};


#endif //CHESS_STOCKFISHBOT_H
