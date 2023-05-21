#include "Game.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"
#include "pieces/Knight.h"
#include "pieces/Queen.h"
#include "Board.h"
#include "pieces/Pawn.h"
#include "Color.h"
#include "Player.h"

Game::Game() {
    this->board = Board::startingBoard();
    this->whitePlayer = new Player("White");    // TODO
    this->blackPlayer = new Player("Black");    // TODO
    this->currentPlayer = whitePlayer;
    this->moveHistory = {};

}

Game::~Game() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

Board *Game::getBoard() {
    return board;
}

Player *Game::getCurrentPlayer() {
    return currentPlayer;
}

std::vector<Move> &Game::getMoveHistory() {
    return moveHistory;
}

bool Game::isMate() const {
    return false;  //TODO
}

bool Game::isCheck() const {
    return false;  // TODO
}

void Game::makeMove(Move move) {
    this->currentPlayer = (this->currentPlayer == this->whitePlayer) ? blackPlayer : whitePlayer;
    this->moveHistory.push_back(move);
    this->board->makeMove(move);
}
