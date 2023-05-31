//
// Created by Admin on 2023-05-21.
//

#ifndef CHESS_CLICKABLE_LABEL_H
#define CHESS_CLICKABLE_LABEL_H

#include <QLabel>


class ClickableLabel : public QLabel {
Q_OBJECT


protected:
    bool clicked;

public:


    ClickableLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    ClickableLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void mousePressEvent(QMouseEvent *event) override;


};


#endif //CHESS_CLICKABLE_LABEL_H
