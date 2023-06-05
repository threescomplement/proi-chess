#include "GameField.h"
#include "Color.h"
#include "pieces/PieceType.h"
#include "mainwindow.h"
#include "ChessIcons.h"
#include <QMouseEvent>
#include <map>
#include <string>
#include <QColor>


static int fieldSize = 50;

std::map<PieceType, std::string> pieceChars{
        {PieceType::NONE,   ""},
        {PieceType::PAWN,   "♟"},
        {PieceType::ROOK,   "♜"},
        {PieceType::BISHOP, "♝"},
        {PieceType::KNIGHT, "♞"},
        {PieceType::KING,   "♚"},
        {PieceType::QUEEN,  "♛"},
};


GameField::GameField(const QString &text, int x, int y, QWidget *parent, Qt::WindowFlags f) :
        ClickableLabel(text, parent, f), marked(false) {
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    this->setFont(font);
    this->x = x;
    this->y = y;
    overlay = new QLabel(this);
    overlay->setGeometry(0, 0, fieldSize, fieldSize);
    overlay->show();
    overlay->raise();
    setMark(false);
}

GameField::~GameField() noexcept {
    // destructor calls will propagate upwards the inheritance tree, so everything will be cleaned up
    delete overlay;

}


/**
 *
 * @param called_x - identifies which field was called to update
 * @param called_y - identifies which field was called to update
 * @param type - SUBJECT TO CHANGE: the type of piece it's supposed to now hold
 * @param mark - the new state of being marked, false by default
 **/
void GameField::updatePieceCalled(int called_x, int called_y, Piece *piece) {
    if (called_x == x && called_y == y) {
        setPiece(piece);
    }
}


void GameField::mousePressEvent(QMouseEvent *event) {
    ClickableLabel::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit fieldClicked(this);
    }
}

void GameField::setPiece(Piece* piece) {

    std::string fileName;

    if (piece != nullptr){
        auto color = piece->getColor();
        auto type = piece->getType();
        if (color == Color::WHITE) {
            fileName += "White_";
        } else {
            fileName += "Black_";
        }
        switch (type) {
            case PieceType::NONE:
                break;
            case PieceType::KING:
                fileName += "king";
                break;
            case PieceType::KNIGHT:
                fileName += "knight";
                break;
            case PieceType::PAWN:
                fileName += "pawn";
                break;
            case PieceType::QUEEN:
                fileName += "queen";
                break;
            case PieceType::ROOK:
                fileName += "rook";
                break;
            case PieceType::BISHOP:
                fileName += "bishop";
        }
    }

    QPixmap pixmap = icons.pieceImgs[fileName];
    this->setPixmap(pixmap.scaled(fieldSize, fieldSize, Qt::AspectRatioMode::KeepAspectRatio));

}

int GameField::getX() const {
    return x;
}

int GameField::getY() const {
    return y;
}


void GameField::reset() {
    setPiece(nullptr);
    clicked = false;
    setMark(false);
}

void GameField::setMark(bool new_mark) {

    marked = new_mark;
    if (marked) {
        overlay->setPixmap(
                QPixmap(":/resources/green_selection_mask_rectangular.png").scaled(fieldSize, fieldSize,
                                                                                   Qt::AspectRatioMode::KeepAspectRatio));
    } else {
        overlay->setPixmap(QPixmap());
    }
}

void GameField::markUpdateCalled(int called_x, int called_y, bool new_mark) {
    if (this->x == called_x and called_y == this->y) {
        setMark(new_mark);
    }
}

