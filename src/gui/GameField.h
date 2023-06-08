
/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_GAMEFIELD_H
#define CHESS_GAMEFIELD_H

#include "ClickableLabel.h"
#include "pieces/PieceType.h"
#include "Color.h"
#include "pieces/Piece.h"


/**
 * @class GameField
 *
 * inherits from ClickableLabel
 *
 * communicates with MainWindow using
 * the updatePieceCalled slot  (comes in)
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
    bool marked;
    int x;
    int y;
    QLabel *overlay;

public:
    GameField(const QString &text, int x, int y, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    ~GameField() noexcept override;

    void setPiece(Piece *piece = nullptr);

    void mousePressEvent(QMouseEvent *event) override;

    int getX() const;

    int getY() const;

    void setMark(bool new_mark);

public slots:

    void reset();

    /**
     *
     * @param called_x - identifies which field was called to update
     * @param called_y - identifies which field was called to update
     * @param type - SUBJECT TO CHANGE: the type of piece it's supposed to now hold
     * @param mark - the new state of being marked, false by default
     **/
    void updatePieceCalled(int called_x, int called_y, Piece *piece = nullptr);

    void markUpdateCalled(int called_x, int called_y, bool new_mark);

signals:

    void fieldClicked(GameField *field);

};


#endif //CHESS_GAMEFIELD_H
