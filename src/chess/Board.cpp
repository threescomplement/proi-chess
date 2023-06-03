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
#include "ChessExceptions.h"

Board::Board() {
    this->allPieces = {};
    this->blackKing = nullptr;
    this->whiteKing = nullptr;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            this->fields[row][col] = new Field(nullptr, Position(row + 1, col + 1), this);
        }
    }
};

Board::~Board() {
    for (auto piecePtr: allPieces) {
        delete piecePtr;
    }

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            delete this->fields[row][col];
        }
    }

}

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
    return new Board();
}

Field *Board::getField(Position position) const {
    return fields[position.getRow() - 1][position.getCol() - 1];
}


Board *Board::startingBoard() {
    auto board = Board::emptyBoard();

    for (int col = 1; col <= BOARD_SIZE; col++) {
        board->allPieces.push_back(new Pawn(Color::WHITE, board->getField(Position(2, col))));
    }

    for (int col = 1; col <= BOARD_SIZE; col++) {
        board->allPieces.push_back(new Pawn(Color::BLACK, board->getField(Position(7, col))));
    }

    board->allPieces.push_back(new Rook(Color::WHITE, board->getField(Position::fromString("a1"))));
    board->allPieces.push_back(new Knight(Color::WHITE, board->getField(Position::fromString("b1"))));
    board->allPieces.push_back(new Bishop(Color::WHITE, board->getField(Position::fromString("c1"))));
    board->allPieces.push_back(new Queen(Color::WHITE, board->getField(Position::fromString("d1"))));
    board->allPieces.push_back(new Bishop(Color::WHITE, board->getField(Position::fromString("f1"))));
    board->allPieces.push_back(new Knight(Color::WHITE, board->getField(Position::fromString("g1"))));
    board->allPieces.push_back(new Rook(Color::WHITE, board->getField(Position::fromString("h1"))));

    board->allPieces.push_back(new Rook(Color::BLACK, board->getField(Position::fromString("a8"))));
    board->allPieces.push_back(new Knight(Color::BLACK, board->getField(Position::fromString("b8"))));
    board->allPieces.push_back(new Bishop(Color::BLACK, board->getField(Position::fromString("c8"))));
    board->allPieces.push_back(new Queen(Color::BLACK, board->getField(Position::fromString("d8"))));
    board->allPieces.push_back(new Bishop(Color::BLACK, board->getField(Position::fromString("f8"))));
    board->allPieces.push_back(new Knight(Color::BLACK, board->getField(Position::fromString("g8"))));
    board->allPieces.push_back(new Rook(Color::BLACK, board->getField(Position::fromString("h8"))));

    auto whiteKing = new King(Color::WHITE, board->getField(Position::fromString("e1")));
    auto blackKing = new King(Color::BLACK, board->getField(Position::fromString("e8")));
    board->whiteKing = whiteKing;
    board->blackKing = blackKing;
    board->allPieces.push_back(whiteKing);
    board->allPieces.push_back(blackKing);

    // Set pointers in both ways
    for (auto piece: board->allPieces) {
        piece->getField()->setPiece(piece);
    }

    return board;
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
                    piece = new Pawn(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'P': {
                    piece = new Pawn(Color::WHITE, board->fields[row][col]);
                    break;
                }
                case 'r': {
                    piece = new Rook(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'R': {
                    piece = new Rook(Color::WHITE, board->fields[row][col]);
                    break;
                }
                case 'n': {
                    piece = new Knight(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'N': {
                    piece = new Knight(Color::WHITE, board->fields[row][col]);
                    break;
                }
                case 'b': {
                    piece = new Bishop(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'B': {
                    piece = new Bishop(Color::WHITE, board->fields[row][col]);
                    break;
                }
                case 'q': {
                    piece = new Queen(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'Q': {
                    piece = new Queen(Color::WHITE, board->fields[row][col]);
                    break;
                }
                case 'k': {
                    piece = new King(Color::BLACK, board->fields[row][col]);
                    break;
                }
                case 'K': {
                    piece = new King(Color::WHITE, board->fields[row][col]);
                    break;
                }
                default:
                    throw FenException("Invalid FEN representation of Game");
            }
            board->allPieces.push_back(piece);
            board->fields[row][col]->setPiece(piece);
            col += 1;
        }
    }
    return board;
}

void Board::makeMove(Move move) {
    auto targetField = this->getField(move.getTo());
    auto sourceField = this->getField(move.getFrom());
    auto targetPiece = targetField->getPiece();
    auto sourcePiece = sourceField->getPiece();

    if (sourceField->isEmpty()) {
        throw IllegalMoveException("Cannot move from empty field");
    }

    if (!targetField->isEmpty() && targetPiece->getColor() == sourcePiece->getColor()) {
        throw IllegalMoveException("Player cannot capture his own piece");
    }


    targetField->setPiece(sourcePiece);
    sourceField->setPiece(nullptr);

    sourcePiece->setField(targetField);
    if (targetPiece != nullptr) {
        targetPiece->setField(nullptr);
    }

    if (move.isCastling()) {
        auto rookCol = (move.isLongCastle()) ? 1 : 8;
        auto row = (move.getTo().getRow());
        auto castledRook = getField(Position(row, rookCol))->getPiece();
        makeMove(Move::generateCastlingComplement(castledRook));
    }
}

const std::vector<Piece *> &Board::getAllPieces() const {
    return allPieces;
}

Piece *Board::getBlackKing() const {
    return blackKing;
}

Piece *Board::getWhiteKing() const {
    return whiteKing;
}

