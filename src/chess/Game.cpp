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

}

Game::~Game() {
    for (Piece *piece: allPieces) {
        delete piece;
    }
}

Board *Game::getBoard() {
    return board;
}

Player *Game::getCurrentPlayer() {
    return whitePlayer;
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
