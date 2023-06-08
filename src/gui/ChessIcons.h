/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_CHESSICONS_H
#define CHESS_CHESSICONS_H

#include <QPixmap>
#include <string>
#include <map>
#include "pieces/PieceType.h"
#include "Color.h"

/**
 * Singleton pattern
 */
class ChessIcons {
protected:
    std::map<std::pair<Color, PieceType>, QPixmap> pieceImgs;

    static ChessIcons *instance;

    ChessIcons();

public:
    QPixmap getPixmap(Color color, PieceType type);

    static ChessIcons *getIcons();
};


#endif //CHESS_CHESSICONS_H
