#include "GameState.h"
#include "Player.h"
#include "Color.h"
#include "Move.h"
#include "Game.h"
#include "pieces/Pawn.h"

void GameState::updateFullmoveNumber() {
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

void GameState::updateEnPassantTarget(Pawn *oldEnPassantTarget) {
    if (this->enPassantTargetPosition != nullptr) {
        oldEnPassantTarget->setIsEnPassantTarget(false);
        this->enPassantTargetPosition = nullptr;
    }
}

void GameState::updateCastling(const Move &move) {
    if (move.getPiece()->getType() == PieceType::KING) {
        if (move.getPiece()->getColor() == Color::WHITE) {
            this->canWhiteKingsideCastle = false;
            this->canWhiteQueensideCastle = false;
        } else {
            this->canBlackKingsideCastle = false;
            this->canBlackQueensideCastle = false;
        }

    } else if (move.getPiece()->getType() == PieceType::ROOK) {
        if (move.getPiece()->getColor() == Color::WHITE) {
            if (move.getFrom().getRow() == 1 && move.getFrom().getCol() == 1) {
                this->canWhiteQueensideCastle = false;
            } else if (move.getFrom().getRow() == 1 && move.getFrom().getCol() == 8) {
                this->canWhiteKingsideCastle = false;
            }
        } else {
            if (move.getFrom().getRow() == 8 && move.getFrom().getCol() == 1) {
                this->canBlackQueensideCastle = false;
            } else if (move.getFrom().getRow() == 8 && move.getFrom().getCol() == 8) {
                this->canBlackKingsideCastle = false;
            }
        }
    }
    if (move.isCapture() && move.getCapturedPiece()->getType() == PieceType::ROOK) {
        this->updateCastlingAfterRookCapture(move.getCapturedPiece());
    }
}

void GameState::updateCastlingAfterRookCapture(const Piece *capturedRook) {
    if (capturedRook->getPosition() == Position(1, 1)) {
        this->canWhiteQueensideCastle = false;
    } else if (capturedRook->getPosition() == Position(1, 8)) {
        this->canWhiteKingsideCastle = false;
    }
    if (capturedRook->getPosition() == Position(8, 1)) {
        this->canBlackQueensideCastle = false;
    } else if (capturedRook->getPosition() == Position(8, 8)) {
        this->canBlackKingsideCastle = false;
    }
}

void GameState::update(const Move &move, Pawn *oldEnPassantTarget) {
    this->updateFullmoveNumber();
    this->updateHalfmoveClock(move);
    this->updateEnPassantTarget(oldEnPassantTarget);
    this->updateCastling(move);
}

GameState GameState::copy(const Game &original, const Game &copied) const {
    return {
            (original.getCurrentPlayer()->getColor() == Color::WHITE) ? copied.getWhitePlayer() : copied.getBlackPlayer(),
            canWhiteKingsideCastle,
            canWhiteQueensideCastle,
            canBlackKingsideCastle,
            canBlackQueensideCastle,
            (enPassantTargetPosition != nullptr) ? Position::copy(*enPassantTargetPosition) : nullptr,
            halfmoveClock,
            fullmoveNumber
    };
}

GameState::GameState(Player *currentPlayer, bool canWhiteKingsideCastle, bool canWhiteQueensideCastle,
                     bool canBlackKingsideCastle, bool canBlackQueensideCastle, Position *enPassantTargetPosition,
                     int halfmoveClock, int fullmoveNumber) : currentPlayer(currentPlayer),
                                                              canWhiteKingsideCastle(canWhiteKingsideCastle),
                                                              canWhiteQueensideCastle(canWhiteQueensideCastle),
                                                              canBlackKingsideCastle(canBlackKingsideCastle),
                                                              canBlackQueensideCastle(canBlackQueensideCastle),
                                                              enPassantTargetPosition(enPassantTargetPosition),
                                                              halfmoveClock(halfmoveClock),
                                                              fullmoveNumber(fullmoveNumber) {}

GameState::GameState() {}
