#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Player.h"


Game::Game(std::string whiteName, std::string blackName) {
    this->board = Board::startingBoard();
    this->whitePlayer = new Player(whiteName);
    this->blackPlayer = new Player(blackName);
    this->currentPlayer = whitePlayer;
    this->moveHistory = {};

    for (Piece *piece: board->getAllPieces()) {
        if (piece->getColor() == Color::WHITE) {
            whitePlayer->getPieces().push_back(piece);
        } else {
            blackPlayer->getPieces().push_back(piece);
        }
    }
}

Game::~Game() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

Board *Game::getBoard() const {
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

Player *Game::getWhitePlayer() const {
    return whitePlayer;
}

Player *Game::getBlackPlayer() const {
    return blackPlayer;
}
