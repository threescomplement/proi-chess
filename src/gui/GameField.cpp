
#include "GameField.h"
#include "pieces/PieceType.h"
#include <QMouseEvent>
#include <map>
#include <string>


std::map<PieceType, std::string> pieceChars {
        {PieceType::NONE, ""},
        {PieceType::PAWN, "♟"},
        {PieceType::ROOK, "♜"},
        {PieceType::BISHOP, "♝"},
        {PieceType::KNIGHT, "♞"},
        {PieceType::KING, "♛"},
        {PieceType::QUEEN, "♚"},
};


void GameField::update_called(int called_x, int called_y, PieceType type) {
    if (called_x == x && called_y == y) {
        clicked = !clicked;

        setPiece(pieceChars[type]);
    }
}

void GameField::mousePressEvent(QMouseEvent *event) {
    ClickableLabel::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        emit fieldClicked(x, y);
    }
}

void GameField::setPiece(std::string new_piece) {
    piece = new_piece;
    QString new_text = QString::fromStdString(piece);
    this->setText(new_text);

}

GameField::GameField(const QString &text, int x, int y, QWidget *parent, Qt::WindowFlags f) : ClickableLabel(text,
                                                                                                             parent,
                                                                                                             f) {
    QFont font = this->font();
    font.setPointSize(20);
    font.setBold(true);
    this->setFont(font);
    this->x = x;
    this->y = y;
}
