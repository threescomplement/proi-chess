#include <Board.h>
#include <QObject>
#include <QProcess>
#include <QCoreApplication>


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Create a QProcess instance
    QProcess stockfishProcess;

    // Set the command to be executed
    QString stockfishProgram = "/home/mgarbowski/stockfish_15.1_linux_x64/stockfish-ubuntu-20.04-x86-64";

    // Start the Stockfish process
    stockfishProcess.start(stockfishProgram);

    // Wait for Stockfish to initialize
    if (stockfishProcess.waitForStarted()) {
        qDebug() << "Stockfish started.";

        // Set up the chess position
        QString positionCommand = "position startpos\n";
        stockfishProcess.write(positionCommand.toUtf8());
        stockfishProcess.waitForBytesWritten();
        stockfishProcess.waitForReadyRead();

        // Read the output from Stockfish
        QByteArray output = stockfishProcess.readAll();
        QString outputString = QString::fromUtf8(output);
        qDebug() << "Output: " << outputString;

        // Retrieve the next move with depth 1
        QString nextMoveCommand = "go depth 1\n";
        stockfishProcess.write(nextMoveCommand.toUtf8());
        stockfishProcess.waitForBytesWritten();

        // Read the output from Stockfish line by line
        QTextStream stream(&stockfishProcess);
        QString line;
        QString nextMove;

        while (true) {
            stockfishProcess.waitForReadyRead();
            line = stream.readLine();
            qDebug() << line;

            if (line.startsWith("info depth 1")) {
                line = stream.readLine();
                QStringList parts = line.split(" ");
                nextMove = parts[1];
                break;
            }
        }

        qDebug() << "Next Move: " << nextMove;
    } else {
        // Error occurred
        qDebug() << "Error: Failed to start Stockfish.";
    }

    // Terminate the Stockfish process
    stockfishProcess.terminate();
    stockfishProcess.waitForFinished();

    return a.exec();
}