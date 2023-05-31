
#ifndef CHESS_GAMEFIELD_H
#define CHESS_GAMEFIELD_H

#include "ClickableLabel.h"
#include "pieces/PieceType.h"


/**
 * @class GameField
 *
 * inherits from ClickableLabel
 *
 * communicates with MainWindow using
 * the updateCalled slot  (comes in)
 * and fieldCLicked signal (goes out)
 *
 *  @param x - column of the board counted from left to right, starting at 1
 *  @param y - row of the board, counted from top to bottom, starting at 1
 *  @param marked - whether the field should be highlighted on the board or not
 *  @param piece - the piece type currently on this field this might later be replaced with a icon file name
 *
 */

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

    void updateCalled(int called_x, int called_y, PieceType type = PieceType::NONE, bool mark = false);

signals:

    void fieldClicked(GameField *field);

};


#endif //CHESS_GAMEFIELD_H
