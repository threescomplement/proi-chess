
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
}

/**
 *
 * @param called_x - identifies which field was called to update
 * @param called_y - identifies which field was called to update
 * @param type - SUBJECT TO CHANGE: the type of piece it's supposed to now hold
 * @param mark - the new state of being marked, false by default
 */
void GameField::updateCalled(int called_x, int called_y, PieceType type, bool mark) {
    if (called_x == x && called_y == y) {
        clicked = !clicked;
        marked = mark;
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
    marked = false;
    // update the label containing the mark overlay
}
