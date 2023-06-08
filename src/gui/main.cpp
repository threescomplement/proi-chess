/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "mainwindow.h"
#include "Game.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto game = new Game("bialy", "czarny");
    auto  w = MainWindow(game);
    w.setWindowTitle("Chess");
    w.setWindowIcon(QIcon(QPixmap(":/resources/White_pawn.png")));
    w.show();
    return a.exec();
}
