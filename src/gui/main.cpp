#include <QApplication>
#include <QPushButton>
#include <Board.h>
#include <iostream>

int main(int argc, char *argv[]) {
    auto board = Board::emptyBoard();
    std::cout << board->toFEN();
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
