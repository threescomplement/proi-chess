
#ifndef CHESS_GAMEFIELD_H
#define CHESS_GAMEFIELD_H

#include "clickable_label.h"

class GameField : public ClickableLabel {

Q_OBJECT

private:
    std::string piece;
    int x;
    int y;
public:
    GameField(const QString &text, int x, int y, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setPiece(std::string new_piece);

    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void update_called(int called_x, int called_y, int piece_number = -1);

signals:

    void fieldClicked(int x, int y);

};


#endif //CHESS_GAMEFIELD_H
