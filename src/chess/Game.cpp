#include "Game.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"
#include "pieces/Knight.h"
#include "pieces/Queen.h"
#include "pieces/Pawn.h"

Game::Game() {
    this->board = Board::emptyBoard();
    this->whitePlayer = Player("White Player");
    this->blackPlayer = Player("Black Player");
    this->currentPlayer = whitePlayer;
    this->moveHistory = {};
    this->allPieces = {};

    whitePlayer.getPieces().push_back(new Rook(Color::WHITE, board.getField(Position(1,1)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Knight(Color::WHITE, board.getField(Position(1,2)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Bishop(Color::WHITE, board.getField(Position(1,3)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Queen(Color::WHITE, board.getField(Position(1,4)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Queen(Color::WHITE, board.getField(Position(1,5)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Bishop(Color::WHITE, board.getField(Position(1,6)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Knight(Color::WHITE, board.getField(Position(1,7)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Rook(Color::WHITE, board.getField(Position(1,8)), &whitePlayer));

    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,1)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,2)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,3)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,4)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,5)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,6)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,7)), &whitePlayer));
    whitePlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(2,8)), &whitePlayer));

    blackPlayer.getPieces().push_back(new Rook(Color::WHITE, board.getField(Position(8,1)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Knight(Color::WHITE, board.getField(Position(8,2)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Bishop(Color::WHITE, board.getField(Position(8,3)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Queen(Color::WHITE, board.getField(Position(8,4)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Queen(Color::WHITE, board.getField(Position(8,5)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Bishop(Color::WHITE, board.getField(Position(8,6)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Knight(Color::WHITE, board.getField(Position(8,7)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Rook(Color::WHITE, board.getField(Position(8,8)), &blackPlayer));

    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,1)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,2)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,3)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,4)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,5)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,6)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,7)), &blackPlayer));
    blackPlayer.getPieces().push_back(new Pawn(Color::WHITE, board.getField(Position(7,8)), &blackPlayer));

    allPieces.insert(allPieces.end(), whitePlayer.getPieces().begin(), whitePlayer.getPieces().end());
    allPieces.insert(allPieces.end(), blackPlayer.getPieces().begin(), blackPlayer.getPieces().end());

    for (Piece *piece: allPieces) {
        piece->getField()->setPiece(piece);
    }

    board.setBlackKing(board.getField(Position(8, 5))->getPiece());
    board.setWhiteKing(board.getField(Position(1, 5))->getPiece());

}

Game::~Game() {
    for (Piece *piece: allPieces) {
        delete piece;
    }
}

Board &Game::getBoard() {
    return board;
}

Player &Game::getCurrentPlayer() const {
    return currentPlayer;
}
