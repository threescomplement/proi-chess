#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <sstream>
#include "../bot/StockfishBot.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string fen = "rnbqkbnr/pppp1ppp/4p3/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq d3 0 2";

    auto bot = StockfishBot();
    auto bestMove = bot.getStockfishOutput(fen);

    // Print the best move
    qDebug() << "The best move is" << bestMove;

    return a.exec();
}
