#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto game = new Game("bialy", "czarny");
    auto  w = MainWindow(game);
    w.show();
    return a.exec();
}
