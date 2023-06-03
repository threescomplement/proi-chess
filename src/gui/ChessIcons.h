
#ifndef CHESS_CHESSICONS_H
#define CHESS_CHESSICONS_H

#include <QPixmap>
#include <string>

class ChessIcons {
public:
    std::map<std::string, QPixmap> pieceImgs = {
            {"",   QPixmap("")},
            {"White_pawn",   QPixmap(":/resources/White_pawn.png")},
            {"Black_pawn", QPixmap(":/resources/Black_pawn.png")},
            {"White_rook",   QPixmap(":/resources/White_rook.png")},
            {"Black_rook", QPixmap(":/resources/Black_rook.png")},
            {"White_bishop",   QPixmap(":/resources/White_bishop.png")},
            {"Black_bishop", QPixmap(":/resources/Black_bishop.png")},
            {"White_knight",   QPixmap(":/resources/White_knight.png")},
            {"Black_knight", QPixmap(":/resources/Black_knight.png")},
            {"White_king",   QPixmap(":/resources/White_king.png")},
            {"Black_king", QPixmap(":/resources/Black_king.png")},
            {"White_queen",   QPixmap(":/resources/White_queen.png")},
            {"Black_queen", QPixmap(":/resources/Black_queen.png")}
    };

};


#endif //CHESS_CHESSICONS_H
