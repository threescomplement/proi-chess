/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include <map>
#include <algorithm>
#include <utility>
#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Player.h"
#include "pieces/PieceType.h"
#include "ChessExceptions.h"
#include "pieces/Pawn.h"
#include "GameOver.h"
#include "FENParser.h"
#include "HistoryManager.h"


Game::Game(std::string whiteName, std::string blackName) {
    this->board = Board::startingBoard();
    this->whitePlayer = new Player(std::move(whiteName), Color::WHITE);
    this->blackPlayer = new Player(std::move(blackName), Color::BLACK);
    this->gameState.currentPlayer = whitePlayer;
    this->history = new HistoryManager();

    this->gameState.canWhiteKingsideCastle = true;
    this->gameState.canWhiteQueensideCastle = true;
    this->gameState.canBlackKingsideCastle = true;
    this->gameState.canBlackQueensideCastle = true;
    this->gameState.enPassantTargetPosition = nullptr;
    this->gameState.halfmoveClock = 0;
    this->gameState.fullmoveNumber = 1;
    this->positionCount = {{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", 1}};

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
    delete history;
}

Board *Game::getBoard() const {
    return board;
}

Player *Game::getCurrentPlayer() const {
    return gameState.currentPlayer;
}

bool Game::isMate() {
    return (isCheck(gameState.currentPlayer->getColor()) && getLegalMovesForPlayer(gameState.currentPlayer).empty());
}

bool Game::isStalemate() {
    return (!isCheck(gameState.currentPlayer->getColor()) && getLegalMovesForPlayer(gameState.currentPlayer).empty());
}

void Game::makeMove(const Move &move, bool updateHistory) {
    if (this->getCurrentPlayer()->getColor() != move.getPiece()->getColor()) {
        throw IllegalMoveException("Player can only move his own piece");
    }

    if (updateHistory) {
        history->update(move, gameState);
    }

    gameState.update(move, this->getEnPassantTargetPiece());

    this->board->makeMove(move);
    if (move.getPromoteTo() != PieceType::NONE) {
        gameState.currentPlayer->removePiece(move.getPiece());
        gameState.currentPlayer->getPieces().push_back(getPiece(move.getTo()));
    }
    if (move.isDoublePawnMove()) {
        auto row = (move.getFrom().getRow() + move.getTo().getRow()) / 2;
        auto col = move.getTo().getCol();
        this->gameState.enPassantTargetPosition = new Position(row, col);
        auto movedPawn = dynamic_cast<Pawn *>(move.getPiece());
        movedPawn->setIsEnPassantTarget(true);
    }

    if (move.isCapture()) {
        auto captured = move.getCapturedPiece();
        auto player = (captured->getColor() == Color::WHITE) ? whitePlayer : blackPlayer;
        player->removePiece(captured);
    }

    auto fenOfCurrentBoard = FENParser::boardToString(*(this->board)); // todo: what about this?
    positionCount[fenOfCurrentBoard] = (positionCount.find(fenOfCurrentBoard) == positionCount.end()) ? 1 :
                                       positionCount[fenOfCurrentBoard] + 1;
    this->switchCurrentPlayer();
}

Player *Game::getWhitePlayer() const {
    return whitePlayer;
}

Player *Game::getBlackPlayer() const {
    return blackPlayer;
}


Piece *Game::getPiece(Position position) const {
    return this->getBoard()->getField(position)->getPiece();
}

Game::Game(
        Board *board,
        Player *whitePlayer,
        Player *blackPlayer,
        Player *currentPlayer,
        bool canWhiteKingsideCastle,
        bool canWhiteQueensideCastle,
        bool canBlackKingsideCastle,
        bool canBlackQueensideCastle,
        Position *enPassantTarget,
        int halfmoveClock,
        int fullmoveNumber
) :
        board(board),
        whitePlayer(whitePlayer),
        blackPlayer(blackPlayer),
        positionCount({}) {
    this->gameState.canWhiteKingsideCastle = canWhiteKingsideCastle;
    this->gameState.canWhiteQueensideCastle = canWhiteQueensideCastle;
    this->gameState.canBlackKingsideCastle = canBlackKingsideCastle;
    this->gameState.canBlackQueensideCastle = canBlackQueensideCastle;
    this->gameState.enPassantTargetPosition = enPassantTarget;
    this->gameState.halfmoveClock = halfmoveClock;
    this->gameState.fullmoveNumber = fullmoveNumber;
    this->gameState.currentPlayer = currentPlayer;
    this->history = new HistoryManager();
}

std::vector<Move> Game::getMovesFrom(Position position) const {
    auto piece = this->getPiece(position);
    if (piece == nullptr)
        return {};

    auto movesForPiece = piece->getMoves();
    if (piece->getType() == PieceType::KING) {
        if (possibleKingsideCastlingThisRound()) {
            movesForPiece.push_back(generateKingSideCastle());
        }
        if (possibleQueensideCastlingThisRound()) {
            movesForPiece.push_back(generateQueenSideCastle());
        }
    }
    return movesForPiece;
}

std::vector<Move> Game::getAllMovesForPlayer(Player *player) const {
    std::vector<Move> moves;
    for (auto piece: player->getPieces()) {
        auto pieceMoves = getMovesFrom(piece->getPosition());
        moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
    }
    return moves;
}

std::vector<Move> Game::getLegalMovesFrom(Position position) {
    auto piece = this->getPiece(position);
    if (piece == nullptr || piece->getColor() != gameState.currentPlayer->getColor())
        return {};

    auto pieceColor = piece->getColor();
    auto movesForPiece = getMovesFrom(position);
    movesForPiece.erase(
            std::remove_if(movesForPiece.begin(), movesForPiece.end(), [pieceColor, this](const Move &m) {
                this->makeMove(m);
                bool illegal = (this->isCheck(pieceColor));
                this->undoMove();
                return illegal;
            }),
            movesForPiece.end());

    if (piece->getType() == PieceType::KING) {
        // remove moves which are impossible to perform due to opponent's pieces controlling the square between
        // king and rook
        movesForPiece.erase(std::remove_if(movesForPiece.begin(), movesForPiece.end(),
                                           [this](Move &move) {
                                               return this->isCastlingObscuredByOpponent(move) && move.isCastling();
                                           }),
                            movesForPiece.end());
    }
    return movesForPiece;
}

std::vector<Move> Game::getLegalMovesForPlayer(Player *player) {
    std::vector<Move> moves = {};
    for (auto piece: player->getPieces()) {
        auto pieceMoves = getLegalMovesFrom(piece->getPosition());
        moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
    }
    return moves;
}

Pawn *Game::getEnPassantTargetPiece() const {
    if (gameState.enPassantTargetPosition == nullptr)
        return nullptr;

    int targetRow = gameState.enPassantTargetPosition->getRow();
    int targetCol = gameState.enPassantTargetPosition->getCol();
    int rowOffsetFromEPPosition = (gameState.currentPlayer == whitePlayer) ? -1 : 1;

    auto positionOfTargetPiece = Position(targetRow + rowOffsetFromEPPosition, targetCol);
    auto ePTargetPiece = dynamic_cast<Pawn *>(getPiece(positionOfTargetPiece));
    if (ePTargetPiece == nullptr)
        throw std::bad_cast();
    return ePTargetPiece;
}


bool Game::possibleKingsideCastlingThisRound() const {
    if (getCurrentPlayer()->getColor() == Color::WHITE && !gameState.canWhiteKingsideCastle ||
        getCurrentPlayer()->getColor() == Color::BLACK && !gameState.canBlackKingsideCastle) {
        return false;
    }
    int currentPlayerBackRank = (getCurrentPlayer()->getColor() == Color::WHITE) ? 1 : 8;
    auto kingSideRook = getPiece(Position(currentPlayerBackRank, 8));
    auto king = getPiece(Position(currentPlayerBackRank, 5));

    bool canCastle = (noPiecesBetweenKingAndRook(king, kingSideRook));
    return canCastle;
}

bool Game::possibleQueensideCastlingThisRound() const {
    if (getCurrentPlayer()->getColor() == Color::WHITE && !gameState.canWhiteQueensideCastle ||
        getCurrentPlayer()->getColor() == Color::BLACK && !gameState.canBlackQueensideCastle) {
        return false;
    }
    int currentPlayerBackRank = (getCurrentPlayer()->getColor() == Color::WHITE) ? 1 : 8;
    auto queenSideRook = getPiece(Position(currentPlayerBackRank, 1));
    auto king = getPiece(Position(currentPlayerBackRank, 5));

    bool canCastle = (noPiecesBetweenKingAndRook(king, queenSideRook));
    return canCastle;
}

bool Game::noPiecesBetweenKingAndRook(const Piece *king, const Piece *rook) const {
    if (king->getPosition().getRow() != rook->getPosition().getRow())
        throw std::invalid_argument("King and rook can't be in different rows!");

    auto row = king->getPosition().getRow();
    auto lowestColToCheck = std::min(king->getPosition().getCol(), rook->getPosition().getCol()) + 1;
    auto upperLimit = std::max(king->getPosition().getCol(), rook->getPosition().getCol());

    for (int currentCol = lowestColToCheck; currentCol < upperLimit; currentCol++) {
        auto currentPosition = Position(row, currentCol);
        if (getPiece(currentPosition) != nullptr)
            return false;
    }
    return true;
}

Move Game::generateKingSideCastle() const {
    int castlingRank = (gameState.currentPlayer->getColor() == Color::WHITE) ? 1 : 8;
    auto fromPosition = Position(castlingRank, 5);
    auto toPosition = Position(castlingRank, 7);
    return Move(fromPosition, toPosition, getPiece(fromPosition), nullptr);
}

Move Game::generateQueenSideCastle() const {
    int castlingRank = (gameState.currentPlayer->getColor() == Color::WHITE) ? 1 : 8;
    auto fromPosition = Position(castlingRank, 5);
    auto toPosition = Position(castlingRank, 3);
    return Move(fromPosition, toPosition, getPiece(fromPosition), nullptr);
}

bool Game::isFieldControlledByPlayer(const Position &pos, Color colorOfPlayer) const {
    Player *playerThatCouldControlTheField = (colorOfPlayer == Color::WHITE) ? whitePlayer : blackPlayer;
    auto movesForControllingPlayer = getAllMovesForPlayer(playerThatCouldControlTheField);
    auto controlsByNonPawns = std::any_of(movesForControllingPlayer.begin(),
                                          movesForControllingPlayer.end(),
                                          [pos](const Move &m) {
                                              // pawns control different fields than the ones they can move to if they can't capture
                                              return m.getTo() == pos && m.getPiece()->getType() != PieceType::PAWN;
                                          });

    // iterate through all pawns, cast them to pawns and if they are one, check whether any of the controlled
    // fields matches the one we're comparing with
    auto controlsByPawns = std::any_of(playerThatCouldControlTheField->getPieces().begin(),
                                       playerThatCouldControlTheField->getPieces().end(),
                                       [pos](Piece *piece) {
                                           auto castToPawn = dynamic_cast<Pawn *>(piece);
                                           if (castToPawn != nullptr) {
                                               auto positionsControlled = castToPawn->attackedPositions();
                                               return std::any_of(
                                                       positionsControlled.begin(),
                                                       positionsControlled.end(),
                                                       [pos](Position attackedPos) { return pos == attackedPos; });
                                           } else return false;
                                       });
    return controlsByNonPawns || controlsByPawns;
}


bool Game::isCheck(Color colorOfCheckedKing) const {
    auto possiblyCheckedKing = (colorOfCheckedKing == Color::WHITE) ? board->getWhiteKing() : board->getBlackKing();
    Player *possiblyCheckingPlayer = (colorOfCheckedKing == Color::WHITE) ? blackPlayer : whitePlayer;
    auto movesForCheckingPlayer = getAllMovesForPlayer(possiblyCheckingPlayer);
    if (std::any_of(movesForCheckingPlayer.begin(),
                    movesForCheckingPlayer.end(),
                    [possiblyCheckedKing](const Move &m) {
                        return m.getCapturedPiece() == possiblyCheckedKing;
                    }))
        return true;
    return false;
}

Game Game::afterMove(const Move &move) const {
    auto copy = this->deepCopy();
    auto sourcePiece = copy.getPiece(move.getFrom());

    Piece *takenPiece = (move.getCapturedPiece() == nullptr)
                        ? nullptr
                        : copy.getPiece(move.getCapturedPiece()->getPosition());
    auto moveEquivalentForDeepCopy = Move(move.getFrom(), move.getTo(), sourcePiece, takenPiece);
    copy.makeMove(moveEquivalentForDeepCopy);
    return copy;
}

bool Game::isCastlingObscuredByOpponent(Move &move) const {
    if (isCheck(move.getPiece()->getColor()))
        return true;

    auto row = move.getTo().getRow();
    auto lowestColToCheck = std::min(move.getTo().getCol(), move.getFrom().getCol()) + 1;
    auto upperLimit = std::max(move.getTo().getCol(), move.getFrom().getCol());
    auto opponentColor = (move.getPiece()->getColor() == Color::WHITE) ? Color::BLACK : Color::WHITE;
    for (auto col = lowestColToCheck; col < upperLimit; col++) {
        if (isFieldControlledByPlayer(Position(row, col), opponentColor))
            return true;
    }
    return false;
}

GameOver Game::isOver() {
    if (isMate())
        return GameOver::MATE;
    else if (isStalemate())
        return GameOver::STALEMATE;
    else if (isDrawByInsufficientMaterial())
        return GameOver::INSUFFICIENT_MATERIAL;
    else if (isDrawByRepetition())
        return GameOver::THREEFOLD_REPETITION;
    else if (isDrawByFiftyMoveRule())
        return GameOver::FIFTY_MOVE_RULE;
    else
        return GameOver::NOT_OVER;
}

bool Game::isDrawByInsufficientMaterial() const {
    auto whitePieces = std::vector<Piece *>(whitePlayer->getPieces());
    auto blackPieces = std::vector<Piece *>(blackPlayer->getPieces());

    whitePieces.erase(std::remove_if(whitePieces.begin(), whitePieces.end(),
                                     [](Piece *p) { return p->getType() == PieceType::KING; }), whitePieces.end());
    blackPieces.erase(std::remove_if(blackPieces.begin(), blackPieces.end(),
                                     [](Piece *p) { return p->getType() == PieceType::KING; }), blackPieces.end());

    if (whitePieces.empty() && blackPieces.empty())
        return true;
    else if (whitePieces.size() == 1 && blackPieces.empty()) {
        auto whitePiece = whitePieces[0];
        if (whitePiece->getType() == PieceType::BISHOP || whitePiece->getType() == PieceType::KNIGHT)
            return true;
    } else if (whitePieces.empty() && blackPieces.size() == 1) {
        auto blackPiece = blackPieces[0];
        if (blackPiece->getType() == PieceType::BISHOP || blackPiece->getType() == PieceType::KNIGHT)
            return true;
    } else if (whitePieces.size() == 1 && blackPieces.size() == 1) {
        auto whitePiece = whitePieces[0];
        auto blackPiece = blackPieces[0];
        if ((whitePiece->getType() == PieceType::BISHOP || whitePiece->getType() == PieceType::KNIGHT) &&
            (blackPiece->getType() == PieceType::BISHOP || blackPiece->getType() == PieceType::KNIGHT))
            return true;
    }
    return false;
}

bool Game::isDrawByRepetition() const {
    return std::any_of(positionCount.begin(), positionCount.end(), [](const std::pair<std::string, int> &p) {
        return p.second >= 3;
    });
}

Position *Game::getEnPassantTargetPosition() const {
    return gameState.enPassantTargetPosition;
}

bool Game::getCanWhiteKingsideCastle() const {
    return gameState.canWhiteKingsideCastle;
}

bool Game::getCanWhiteQueensideCastle() const {
    return gameState.canWhiteQueensideCastle;
}

bool Game::getCanBlackKingsideCastle() const {
    return gameState.canBlackKingsideCastle;
}

bool Game::getCanBlackQueensideCastle() const {
    return gameState.canBlackQueensideCastle;
}

int Game::getHalfmoveClock() const {
    return gameState.halfmoveClock;
}

int Game::getFullmoveNumber() const {
    return gameState.fullmoveNumber;
}

Game Game::deepCopy() const {
    auto copy = FENParser::parseGame(FENParser::gameToString(*this));
    copy.setPositionCount(std::map<std::string, int>(this->getPositionCount()));
    copy.gameState = this->gameState.copy(*this, copy);
    copy.history = new HistoryManager(*this->history);  // TODO: Are there more params to copy?
    return copy;
}

std::map<std::string, int> Game::getPositionCount() const {
    return positionCount;
}

void Game::setPositionCount(std::map<std::string, int> count) {
    positionCount = std::move(count);
}

bool Game::isDrawByFiftyMoveRule() const {
    return gameState.halfmoveClock >= 100;
}

void Game::undoMove() {
    if (!history->canUndoMove()) {
        return;
    }

    this->switchCurrentPlayer();
    auto fenOfCurrentBoard = FENParser::boardToString(*(this->board));
    positionCount[fenOfCurrentBoard]--;
    auto moveToReverse = history->getMoveToUndo();
    loadPreviousGamestate();
    if (moveToReverse.isCapture()) {
        auto captured = moveToReverse.getCapturedPiece();
        auto player = (captured->getColor() == Color::WHITE) ? whitePlayer : blackPlayer;
        player->getPieces().push_back(captured);
    }
    if (moveToReverse.isDoublePawnMove()) {
        this->gameState.enPassantTargetPosition = nullptr;
        auto movedPawn = dynamic_cast<Pawn *>(moveToReverse.getPiece());
        movedPawn->setIsEnPassantTarget(false);
    }
    if (moveToReverse.getPromoteTo() != PieceType::NONE) {
        gameState.currentPlayer->getPieces().push_back(moveToReverse.getPiece());
        gameState.currentPlayer->removePiece(getPiece(moveToReverse.getTo()));
    }
    bool isEnPassant = (getEnPassantTargetPosition() == nullptr ||
                        moveToReverse.getTo() != *(getEnPassantTargetPosition())) ? false : true;


    board->reverseMove(moveToReverse, isEnPassant);
    if (getEnPassantTargetPiece() != nullptr)
        getEnPassantTargetPiece()->setIsEnPassantTarget(true);
}

void Game::switchCurrentPlayer() {
    gameState.currentPlayer = (gameState.currentPlayer == whitePlayer) ? blackPlayer : whitePlayer;
}

void Game::redoMove() {
    if (!history->canRedoMove()) {
        return;
    }

    auto moveToReverse = history->getMoveToRedo();
    this->makeMove(moveToReverse, false);
}

int Game::getMovesIntoThePast() const {
    return history->getMovesIntoThePast();
}

void Game::loadPreviousGamestate() {
    auto state = this->history->getHistory()[this->history->getHistory().size() - getMovesIntoThePast()].state;
    this->gameState = state.copy(*this, *this);
}


std::vector<std::string> split(const std::string &txt, char ch) {
    std::vector<std::string> strings;
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    while (pos != std::string::npos) {
        strings.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = txt.find(ch, initialPos);
    }

    strings.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
    return strings;
}