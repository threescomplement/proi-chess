
#include "GameField.h"
#include "pieces/PieceType.h"
#include <QMouseEvent>
#include <map>
#include <string>


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
    //overlay->setGeometry(this->geometry());
    int width = this->width();
    int height = this->height();
    overlay->setPixmap(
            QPixmap(":/resources/orange_frame_overlay.png").scaled(50, 50,
                                                                   Qt::AspectRatioMode::KeepAspectRatio));

    //overlay->setPixmap(QPixmap());
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
 */
void GameField::updatePieceCalled(int called_x, int called_y, PieceType type) {
    if (called_x == x && called_y == y) {
        setPiece(type);
    }
}


void GameField::mousePressEvent(QMouseEvent *event) {
    ClickableLabel::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit fieldClicked(this);
    }
}

void GameField::setPiece(PieceType type) {
    QString new_text = QString::fromStdString(pieceChars[type]);
    this->setText(new_text);
}

int GameField::getX() const {
    return x;
}

int GameField::getY() const {
    return y;
}

const PieceType &GameField::getPiece() const {
    return piece;
}

void GameField::reset() {
    setPiece(PieceType::NONE);
    clicked = false;
    setMark(false);
}

void GameField::setMark(bool new_mark) {

    marked = new_mark;
    if (marked) {
        overlay->setPixmap(
                QPixmap(":/resources/orange_frame_overlay.png").scaled(50, 50, Qt::AspectRatioMode::KeepAspectRatio));
    } else {
        overlay->setPixmap(QPixmap());
    }
}

void GameField::markUpdateCalled(int called_x, int called_y, bool new_mark) {
    if (this->x == called_x and called_y == this->y) {
        setMark(new_mark);
    }
}

