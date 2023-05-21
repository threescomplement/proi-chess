#include <QCoreApplication>
#include <QProcess>
#include <QString>
#include <sstream>
#include "../bot/StockfishBot.h"
#include "Move.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    std::string fen = "rnbqkbnr/ppp2ppp/4p3/3p4/3PP3/8/PPP2PPP/RNBQKBNR w KQkq d6 0 3";

    auto game = Game();
    auto bot = StockfishBot(game);

    // Print the best move
    qDebug() << "The best move is" << bot.getMoveFromStockfish(fen).toString();


    return a.exec();
}
