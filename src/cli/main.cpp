#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QString>
#include <sstream>

// A function that starts Stockfish as a separate process, sets a position in FEN notation, retrieves the best move and returns it as a QString
QString getBestMove(std::string fen) {
    // Create a QtProcess object
    QProcess stockfish;

    // Start Stockfish as a separate process
    stockfish.start("/home/mgarbowski/stockfish_15.1_linux_x64/stockfish-ubuntu-20.04-x86-64");

    // Wait for Stockfish to start
    if (!stockfish.waitForStarted()) {
        qDebug() << "Stockfish failed to start";
        return "";
    }

    auto command = "position fen rnbqkbnr/pppp1ppp/4p3/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq d3 0 2\n";

    // Write commands to Stockfish's stdin
    stockfish.write("uci\n"); // Initialize UCI mode
    stockfish.write("ucinewgame\n"); // Start a new game
    stockfish.write(command); // Set the chessboard position in FEN notation
    stockfish.write("go depth 10\n"); // Ask Stockfish to calculate the best move with depth 10

    while (true) {
        stockfish.waitForReadyRead();
        QString output = stockfish.readAll();
        if (output.contains("bestmove")) {
            return output;
        }
    }

    return "";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // A sample FEN position
    std::string fen = "rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";

    // Get the best move for the position
    QString bestMove = getBestMove(fen);

    // Print the best move
    qDebug() << "The best move is" << bestMove;

    return a.exec();
}
