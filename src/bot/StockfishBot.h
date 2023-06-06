#ifndef CHESS_STOCKFISHBOT_H
#define CHESS_STOCKFISHBOT_H


#include <QString>
#include <map>
#include "Game.h"
#include "ChessBot.h"
#include "pieces/PieceType.h"

/**
 * Requires stockfish to be installed and on the system PATH
 */
class StockfishBot : public ChessBot {
private:
    Move getMoveFromStockfish(const std::string& gameFEN) const;

    static const std::string stockfishProgramName;

    QString getStockfishOutput(const std::string& fen) const;

    static QString getStockfishOutput(const char *positionCmd, const char *goCmd);

    static std::string extractMove(const QString& stockfishOutput);

public:

    explicit StockfishBot(const Game &game, int depth = 10);

    Move getBestNextMove() const override;
};


#endif //CHESS_STOCKFISHBOT_H
