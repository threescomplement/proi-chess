#include "mainwindow.h"
#include <QApplication>
#include "../chess//Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Game *game = new Game("bialy", "czarny");
//    delete game;
    MainWindow w;
    w.show();
    return a.exec();
}
