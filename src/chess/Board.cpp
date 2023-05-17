#include <sstream>
#include "Board.h"
#include "Color.h"
#include "Player.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

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
    auto board = new Board();
    std::array<std::array<Field *, 8>, 8> fields = {};
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            fields[row][col] = new Field(nullptr, Position(row + 1, col + 1), board);
        }
    }
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
    result = result.substr(0, result.size() - 1);
    return result;
}

Board *Board::fromFEN(const std::string &FENDescription) {
    auto whitePlayer = new Player("White");
    auto blackPlayer = new Player("Black");
    auto board = Board::emptyBoard();

    int row = 7;
    int col = 0;

    for (auto character: FENDescription) {
        if (isdigit(character)) {
            // empties
            std::string stringOfEmpties = {character};
            col += std::stoi(stringOfEmpties);

        } else if (character == '/') {
            // next row
            row -= 1;
            col = 0;
        } else {
            Piece *piece = nullptr;
            switch (character) {
                case 'p': {
                    piece = new Pawn(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'P': {
                    piece = new Pawn(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                case 'r': {
                    piece = new Rook(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'R': {
                    piece = new Rook(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                case 'n': {
                    piece = new Knight(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'N': {
                    piece = new Knight(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                case 'b': {
                    piece = new Bishop(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'B': {
                    piece = new Bishop(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                case 'q': {
                    piece = new Queen(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'Q': {
                    piece = new Queen(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                case 'k': {
                    piece = new King(Color::BLACK, board->fields[row][col], blackPlayer);
                    break;
                }
                case 'K': {
                    piece = new King(Color::WHITE, board->fields[row][col], whitePlayer);
                    break;
                }
                default:
                    throw std::invalid_argument("Invalid FEN literal in string.");
            }
            board->fields[row][col]->setPiece(piece);
            col += 1;
        }
    }
    return board;
}

