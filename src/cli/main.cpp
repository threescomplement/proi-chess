#include <iostream>
#include <Board.h>

int main() {
    auto board = Board::emptyBoard();
    std::cout << board->toString();
}