#include "ChessIcons.h"

ChessIcons *ChessIcons::instance = nullptr;

ChessIcons::ChessIcons() {
    this->pieceImgs = {
            {{Color::WHITE, PieceType::PAWN},   QPixmap(":/resources/White_pawn.png")},
            {{Color::BLACK, PieceType::PAWN},   QPixmap(":/resources/Black_pawn.png")},
            {{Color::WHITE, PieceType::ROOK},   QPixmap(":/resources/White_rook.png")},
            {{Color::BLACK, PieceType::ROOK},   QPixmap(":/resources/Black_rook.png")},
            {{Color::WHITE, PieceType::BISHOP}, QPixmap(":/resources/White_bishop.png")},
            {{Color::BLACK, PieceType::BISHOP}, QPixmap(":/resources/Black_bishop.png")},
            {{Color::WHITE, PieceType::KNIGHT}, QPixmap(":/resources/White_knight.png")},
            {{Color::BLACK, PieceType::KNIGHT}, QPixmap(":/resources/Black_knight.png")},
            {{Color::WHITE, PieceType::KING},   QPixmap(":/resources/White_king.png")},
            {{Color::BLACK, PieceType::KING},   QPixmap(":/resources/Black_king.png")},
            {{Color::WHITE, PieceType::QUEEN},  QPixmap(":/resources/White_queen.png")},
            {{Color::BLACK, PieceType::QUEEN},  QPixmap(":/resources/Black_queen.png")}
    };
}

ChessIcons *ChessIcons::getIcons() {
    if (ChessIcons::instance == nullptr) {
        ChessIcons::instance = new ChessIcons();
    }

    return ChessIcons::instance;
}

QPixmap ChessIcons::getPixmap(Color color, PieceType type) {
    if (type == PieceType::NONE) {
        return QPixmap("");
    }
    return this->pieceImgs[{color, type}];
}
