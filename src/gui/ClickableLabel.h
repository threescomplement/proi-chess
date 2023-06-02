//
// Created by Admin on 2023-05-21.
//

#ifndef CHESS_CLICKABLELABEL_H
#define CHESS_CLICKABLELABEL_H

#include <QLabel>

/**
 * class ClickLabel
 *
 * a simple class which has all the functionality of a Label
 * with the added bonus of having a mousePressEvent, which toggles
 * the "clicked" attribute when left-clicked
 *
 * word wrapping is set to true by default
 *
 */
class ClickableLabel : public QLabel {
Q_OBJECT


protected:
    bool clicked;

public:


    ClickableLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    ClickableLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void mousePressEvent(QMouseEvent *event) override;


};


#endif //CHESS_CLICKABLELABEL_H
