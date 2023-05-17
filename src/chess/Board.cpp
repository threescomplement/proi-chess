#include <sstream>
#include "Board.h"
#include "Color.h"

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

std::string Board::toFEN() const {
    // TODO: discuss the other fen parameters - castling and so on
    std::stringstream ss;

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int empties = 0;
            auto tempCol = col;
            while (tempCol < BOARD_SIZE && fields[row][tempCol]->isEmpty()) {
                empties++;
                tempCol++;
            }
            if (empties == 0) {
              auto currPieceChar = fields[row][col]->getPiece()->getCharacter();
              ss << currPieceChar;
            } else {
                ss << empties;
                col = col + empties - 1;
            }
        }
        ss << '/';
    }

    std::string result = ss.str();
    result = result.substr(0, result.size()-1);
    return result;
}

