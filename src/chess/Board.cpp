#include <sstream>
#include <algorithm>
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
    auto empty = " ";
    auto separator = "  ";

    for (int row = BOARD_SIZE - 1; row >= 0; --row) {
        ss << row + 1 << separator;
        for (int col = 0; col < BOARD_SIZE; ++col) {
            auto field = fields[row][col];
            if (!field->isEmpty()) {
                ss << field->getPiece()->getUnicodeSymbol() << separator;
            } else {
                ss << empty << separator;
            }
        }
        ss << std::endl;
    }
    ss << empty << separator << "A" << separator << "B" << separator << "C" << separator << "D" << separator << "E"
       << separator << "F" << separator << "G" << separator << "H" << separator << "" << std::endl;

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


void Board::makeMove(const Move &move) {
    auto targetField = this->getField(move.getTo());
    auto sourceField = this->getField(move.getFrom());
    auto pieceOnTargetField = targetField->getPiece();
    auto sourcePiece = sourceField->getPiece();
    auto capturedPiece = move.getCapturedPiece();

    if (sourceField->isEmpty()) {
        throw IllegalMoveException("Cannot move from empty field");
    }

    if (!targetField->isEmpty() && pieceOnTargetField->getColor() == sourcePiece->getColor()) {
        throw IllegalMoveException("Player cannot capture his own piece");
    }

    if (capturedPiece != nullptr) {
        capturedPiece->getField()->setPiece(nullptr);
        capturedPiece->takeOffField();
    }

    if (move.getPromoteTo() == PieceType::NONE) {
        targetField->setPiece(sourcePiece);
        sourceField->setPiece(nullptr);
        sourcePiece->setField(targetField);
        if (move.isCastling()) {
            auto rookCol = (move.isLongCastle()) ? 1 : 8;
            auto row = (move.getTo().getRow());
            auto castledRook = getField(Position(row, rookCol))->getPiece();
            makeMove(Move::generateCastlingComplement(castledRook));
        }
    } else
        this->executePromotion(move);
}


std::vector<Piece *> &Board::getAllPieces() {
    return allPieces;
}

Piece *Board::getBlackKing() const {
    return blackKing;
}

Piece *Board::getWhiteKing() const {
    return whiteKing;
}

void Board::executePromotion(const Move &move) {
    auto sourcePiece = move.getPiece();
    auto targetField = this->getField(move.getTo());
    Piece *promotedPiece;
    switch (move.getPromoteTo()) {
        case PieceType::QUEEN: {
            promotedPiece = new Queen(sourcePiece->getColor(), targetField);
            break;
        }
        case PieceType::ROOK: {
            promotedPiece = new Rook(sourcePiece->getColor(), targetField);
            break;
        }
        case PieceType::BISHOP: {
            promotedPiece = new Bishop(sourcePiece->getColor(), targetField);
            break;
        }
        case PieceType::KNIGHT: {
            promotedPiece = new Knight(sourcePiece->getColor(), targetField);
            break;
        }
        default:
            throw IllegalMoveException("Cannot promote to this piece!");
    }
    promotedPiece->getField()->setPiece(promotedPiece);
    sourcePiece->getField()->setPiece(nullptr);
    sourcePiece->takeOffField();
    allPieces.push_back(promotedPiece);
}

void Board::setBlackKing(Piece *blackKing) {
    Board::blackKing = blackKing;
}

void Board::setWhiteKing(Piece *whiteKing) {
    Board::whiteKing = whiteKing;
}

void Board::reverseMove(const Move &move) {
    auto sourceField = this->getField(move.getTo());
    auto targetField = this->getField(move.getFrom());
    auto sourcePiece = sourceField->getPiece();
    auto capturedPiece = move.getCapturedPiece();

    sourcePiece->setField(targetField);
    targetField->setPiece(sourcePiece);

    if (move.getPromoteTo() == PieceType::NONE) {
        sourceField->setPiece(nullptr);
        //todo - move.iscastlingcomplement
    } else {
        auto promotedPiece = sourceField->getPiece();
        allPieces.erase(std::remove(allPieces.begin(), allPieces.end(), promotedPiece));
        sourceField->setPiece(nullptr);
        promotedPiece->takeOffField();
        delete promotedPiece;
    }

    if (capturedPiece != nullptr) {
        capturedPiece->setField(sourceField);
        sourceField->setPiece(capturedPiece);
    }

}


