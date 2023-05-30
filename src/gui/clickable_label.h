//
// Created by Admin on 2023-05-21.
//

#ifndef CHESS_CLICKABLE_LABEL_H
#define CHESS_CLICKABLE_LABEL_H

#include <QLabel>


class ClickableLabel : public QLabel {
    Q_OBJECT


private:
    bool clicked;
    int x;
    int y;
public:


    ClickableLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    ClickableLabel(const QString &text, int x, int y, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    ClickableLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void mousePressEvent(QMouseEvent *event) override;

public slots:

    void update_called(int called_x, int called_y);

signals:

    void labelClicked(int x, int y);

};


#endif //CHESS_CLICKABLE_LABEL_H
