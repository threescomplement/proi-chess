
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
        {PieceType::KING,   "♛"},
        {PieceType::QUEEN,  "♚"},
};


GameField::GameField(const QString &text, int x, int y, QWidget *parent, Qt::WindowFlags f) : ClickableLabel(text,
                                                                                                             parent,
                                                                                                             f),
                                                                                              marked(false) {
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    this->setFont(font);
    this->x = x;
    this->y = y;
}


void GameField::update_called(int called_x, int called_y, PieceType type, bool mark) {
    if (called_x == x && called_y == y) {
        clicked = !clicked;
        marked = mark;
        setPiece(pieceChars[type]);
    }
}

void GameField::mousePressEvent(QMouseEvent *event) {
    ClickableLabel::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit fieldClicked(this);
    }
}

void GameField::setPiece(std::string new_piece) {
    QString new_text = QString::fromStdString(new_piece);
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
