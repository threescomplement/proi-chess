#ifndef CHESS_STOCKFISHBOT_H
#define CHESS_STOCKFISHBOT_H


#include <QString>

class StockfishBot {
private:
    QString getStockfishOutput(const char *command);

public:

    QString getStockfishOutput(std::string fen);

    std::string extractMove(QString stockfishOutput);
};


#endif //CHESS_STOCKFISHBOT_H
