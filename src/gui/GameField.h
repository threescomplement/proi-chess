
#ifndef CHESS_GAMEFIELD_H
#define CHESS_GAMEFIELD_H

#include "ClickableLabel.h"
#include "pieces/PieceType.h"

class GameField : public ClickableLabel {

Q_OBJECT

private:
    PieceType piece;
    bool marked;
    int x;
    int y;

public:
    GameField(const QString &text, int x, int y, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setPiece(std::string new_piece);

    void mousePressEvent(QMouseEvent *event) override;

    int getX() const;

    int getY() const;

    const PieceType &getPiece() const;

public slots:

    void update_called(int called_x, int called_y, PieceType type = PieceType::NONE, bool mark = false);

signals:

    void fieldClicked(GameField *field);

};


#endif //CHESS_GAMEFIELD_H
