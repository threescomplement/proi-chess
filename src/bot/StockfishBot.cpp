#include <QProcess>
#include <QCoreApplication>
#include <sstream>
#include "StockfishBot.h"
#include "Move.h"
#include "Game.h"
#include "Board.h"

const std::string StockfishBot::stockfishProgramName = "stockfish";

QString StockfishBot::getStockfishOutput(const char *positionCmd, const char *goCmd) {
    // Create a QtProcess object
    QProcess stockfish;

    // Start Stockfish as a separate process
    stockfish.start(StockfishBot::stockfishProgramName.c_str());

    // Wait for Stockfish to start
    if (!stockfish.waitForStarted()) {
        qDebug() << "Stockfish failed to start";
        return "";
    }

    // Write commands to Stockfish's stdin
    stockfish.write("uci\n"); // Initialize UCI mode
    stockfish.write("ucinewgame\n"); // Start a new game
    stockfish.write(positionCmd); // Set the chessboard position in FEN notation
    stockfish.write(goCmd); // Ask Stockfish to calculate the best move with given depth

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

QString StockfishBot::getStockfishOutput(const std::string &fen) const {
    std::stringstream positionCmd;
    positionCmd << "position fen " << fen << "\n";
    std::stringstream goCmd;
    goCmd << "go depth " << this->getDepth() << "\n";

    return StockfishBot::getStockfishOutput(positionCmd.str().c_str(), goCmd.str().c_str());
}

std::string StockfishBot::extractMove(const QString &stockfishOutput) {
    std::string str = stockfishOutput.toStdString();
    std::string pattern = "bestmove ";
    auto idx = str.find(pattern);
    return str.substr(idx + pattern.size(), 4);
}

Move StockfishBot::getMoveFromStockfish(const std::string &gameFEN) const {
    auto moveStr = extractMove(getStockfishOutput(gameFEN));
    auto sourcePosition = Position::fromString(moveStr.substr(0, 2));
    auto targetPosition = Position::fromString(moveStr.substr(2, 2));

    auto board = this->game.getBoard();
    auto movedPiece = board->getField(sourcePosition)->getPiece();
    auto capturedPiece = board->getField(targetPosition)->getPiece();

    return {sourcePosition, targetPosition, movedPiece, capturedPiece};
}

Move StockfishBot::getBestNextMove() const {
    return this->getMoveFromStockfish(game.toFEN());
}

StockfishBot::StockfishBot(const Game &game, int depth) : ChessBot(game, depth) {}
