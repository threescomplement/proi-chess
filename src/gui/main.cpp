#include <QApplication>
#include <QPushButton>
#include <Board.h>

int main(int argc, char *argv[]) {
    auto board = Board::emptyBoard();
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
