#include "Board.h"

//
//Board Board::emptyBoard() {
//    std::array<std::array<Field *, 8>, 8> fields = {};
//    for (int row = 0; row < BOARD_SIZE; ++row) {
//        for (int col = 0; col < BOARD_SIZE; ++col) {
//            fields[row][col] = new Field(nullptr, Position(row, col), nullptr);
//        }
//    }
//
//    auto board = Board();
//    board.fields = fields;
//    board.whiteKing = nullptr;
//    board.blackKing = nullptr;
//    return board;
//}
//
Board::Board() = default;

std::string Board::toString() const {
    std::stringstream ss;
    auto blackSquare = "■";
    auto whiteSquare = "□";

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto field = fields[row][col];
            if (!field->isEmpty()) {
                ss << field->getPiece()->getUnicodeSymbol();
            } else {
                auto symbol = ((row + col) % 2 == 0) ? blackSquare : whiteSquare;
                ss << symbol;
            }
        }
        ss << std::endl;
    }

    return ss.str();
}

Board *Board::emptyBoard() {
    std::array<std::array<Field *, 8>, 8> fields = {};
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            fields[row][col] = new Field(nullptr, Position(row + 1, col + 1), nullptr);
        }
    }

    auto board = new Board();
    board->fields = fields;
    board->whiteKing = nullptr;
    board->blackKing = nullptr;
    return board;
}

Field *Board::getField(Position position) const {
    return fields[position.getRow() - 1][position.getCol() - 1];
}

void Board::setBlackKing(Piece *blackKing) {
    this->blackKing = blackKing;
}

void Board::setWhiteKing(Piece *whiteKing) {
    this->whiteKing = whiteKing;
}
