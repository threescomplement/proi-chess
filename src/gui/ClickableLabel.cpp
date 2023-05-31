
#include "ClickableLabel.h"
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
    }



//    if (clicked) {
//        this->setText(QString("kliknięte"));
//    } else {
//        this->setText(QString("NIE kliknięte"));
//    }
}


