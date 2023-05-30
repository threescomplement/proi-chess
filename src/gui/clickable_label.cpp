
#include "clickable_label.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
        : QLabel(text, parent, f), clicked(false) {

    this->setWordWrap(true);
};

ClickableLabel::ClickableLabel(QWidget *parent, Qt::WindowFlags f) : QLabel(parent, f) {
    this->setWordWrap(true);
};


void ClickableLabel::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        clicked = !clicked;
        emit labelClicked(x, y);
    }

    if (clicked) {
        this->setText(QString("kliknięte"));
    } else {
        this->setText(QString("NIE kliknięte"));
    }
}

ClickableLabel::ClickableLabel(const QString &text, int x, int y, QWidget *parent, Qt::WindowFlags f)
        : QLabel(text, parent, f), clicked(false), x(x), y(y) {
    this->setWordWrap(true);
}

void ClickableLabel::update_called(int called_x, int called_y) {
    if (called_x == x && called_y == y) {
        clicked = !clicked;

        if (clicked) {
            this->setText(QString("kliknięte"));
        } else {
            this->setText(QString("NIE kliknięte"));
        }
    }
}
