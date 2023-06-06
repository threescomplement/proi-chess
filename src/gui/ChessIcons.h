#ifndef CHESS_CHESSICONS_H
#define CHESS_CHESSICONS_H

#include <QPixmap>
#include <string>
#include <map>

/**
 * Singleton pattern
 */
class ChessIcons {
protected:
    std::map<std::string, QPixmap> pieceImgs;

    static ChessIcons *instance;

    ChessIcons();
public:
    QPixmap getPixmap(std::string str);

    static ChessIcons *getIcons();
};



#endif //CHESS_CHESSICONS_H
