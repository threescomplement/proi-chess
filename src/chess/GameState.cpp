#include "GameState.h"
#include "Player.h"
#include "Color.h"
#include "Move.h"
#include "pieces/Pawn.h"

void GameState::updateFullmoveNumber(const Move &move) {
    if (this->currentPlayer->getColor() == Color::BLACK) {
        this->fullmoveNumber++;
    }
}

void GameState::updateHalfmoveClock(const Move &move) {
    this->halfmoveClock++;
    if (move.isCapture() || move.getPiece()->getType() == PieceType::PAWN) {
        this->halfmoveClock = 0;
    }
}

void GameState::updateEnPassantTarget(const Move &move, Pawn *oldEnPassantTarget) {
    if (this->enPassantTargetPosition != nullptr) {
        oldEnPassantTarget->setIsEnPassantTarget(false);
        delete this->enPassantTargetPosition;
        this->enPassantTargetPosition = nullptr;
    }
}

