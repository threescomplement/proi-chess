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

    this->canWhiteKingsideCastle = true;
    this->canWhiteQueensideCastle = true;
    this->canBlackKingsideCastle = true;
    this->canBlackQueensideCastle = true;
    this->enPassantTarget = nullptr;
    this->halfmoveClock = 0;
    this->fullmoveNumber = 1;

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

std::string Game::castlingAvailabilityFEN() const {
    std::stringstream ss;
    if (canWhiteKingsideCastle) {
        ss << "K";
    }
    if (canWhiteQueensideCastle) {
        ss << "Q";
    }
    if (canBlackKingsideCastle) {
        ss << "k";
    }
    if (canBlackQueensideCastle) {
        ss << "q";
    }

    auto result = ss.str();
    if (result.size() == 0) {
        return "-";
    }

    return result;
}

std::string Game::toFEN() const {
    std::stringstream ss;
    auto board = this->getBoard()->toFEN();
    auto activePlayer = (this->currentPlayer == this->whitePlayer) ? "w" : "b";
    auto castling = this->castlingAvailabilityFEN();
    auto enPassant = (this->enPassantTarget != nullptr) ? this->enPassantTarget->toString() : "-";

    ss << board << " "
       << activePlayer << " "
       << castling << " "
       << enPassant << " "
       << this->halfmoveClock << " "
       << this->fullmoveNumber;

    return ss.str();
}
