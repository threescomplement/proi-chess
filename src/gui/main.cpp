#include <iostream>
#include "../chess/Game.h"
#include "mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "Hello" << std::endl;
    Game *game = new Game;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
