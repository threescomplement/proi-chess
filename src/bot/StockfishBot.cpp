#include <QProcess>
#include <QCoreApplication>
#include <sstream>
#include "StockfishBot.h"

QString StockfishBot::getStockfishOutput(const char *command) {
    // Create a QtProcess object
    QProcess stockfish;

    // Start Stockfish as a separate process
    stockfish.start("/home/mgarbowski/stockfish_15.1_linux_x64/stockfish-ubuntu-20.04-x86-64");

    // Wait for Stockfish to start
    if (!stockfish.waitForStarted()) {
        qDebug() << "Stockfish failed to start";
        return "";
    }

    // Write commands to Stockfish's stdin
    stockfish.write("uci\n"); // Initialize UCI mode
    stockfish.write("ucinewgame\n"); // Start a new game
    stockfish.write(command); // Set the chessboard position in FEN notation
    stockfish.write("go depth 10\n"); // Ask Stockfish to calculate the best move with depth 10

    while (true) {
        stockfish.waitForReadyRead();
        QString output = stockfish.readAll();
        if (output.contains("bestmove")) {
            stockfish.kill();
            return output;
        }
    }

    stockfish.kill();
    return "";
}

QString StockfishBot::getStockfishOutput(std::string fen) {
    std::stringstream ss;
    ss << "position fen " << fen << "\n";
    return this->getStockfishOutput(ss.str().c_str());
}

std::string StockfishBot::extractMove(QString stockfishOutput) {
    std::string str = stockfishOutput.toStdString();
    std::string pattern = "bestmove ";
    auto idx = str.find(pattern);
    return str.substr(idx + pattern.size(), 4);
}
