
/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

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
}


