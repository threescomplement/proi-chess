#include <map>
#include <algorithm>
#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Player.h"
#include "pieces/PieceType.h"
#include "ChessExceptions.h"
#include "pieces/Pawn.h"
#include "pieces/PieceType.h"


Game::Game(std::string whiteName, std::string blackName) {
    this->board = Board::startingBoard();
    this->whitePlayer = new Player(whiteName, Color::WHITE);
    this->blackPlayer = new Player(blackName, Color::BLACK);
    this->currentPlayer = whitePlayer;
    this->moveHistory = {};

    this->canWhiteKingsideCastle = true;
    this->canWhiteQueensideCastle = true;
    this->canBlackKingsideCastle = true;
    this->canBlackQueensideCastle = true;
    this->enPassantTargetPosition = nullptr;
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

//bool Game::isCheck() const {
//    return false;  // TODO
//}

void Game::makeMove(Move move) {

    if (this->currentPlayer->getColor() == Color::BLACK) {
        this->fullmoveNumber++;
    }

    this->halfmoveClock++;
    if (move.isCapture() || move.getPiece()->getType() == PieceType::PAWN) {
        this->halfmoveClock = 0;
    }

    if (this->enPassantTargetPosition != nullptr) {
        refreshEnPassant();
    };
    this->refreshCastlingPossibilites(move);

    this->board->makeMove(move);

    if (move.isDoublePawnMove()) {
        auto row = (move.getFrom().getRow() + move.getTo().getRow()) / 2;
        auto col = move.getTo().getCol();
        this->enPassantTargetPosition = new Position(row, col);
        auto movedPawn = dynamic_cast<Pawn *>(move.getPiece());
        movedPawn->setIsEnPassantTarget(true);
    }

    if (move.isCapture()) {
        auto captured = move.getCapturedPiece();
        captured->takeOffField();
        auto player = (captured->getColor() == Color::WHITE) ? whitePlayer : blackPlayer;
        player->removePiece(captured);
    }

    this->moveHistory.push_back(move);
    this->currentPlayer = (this->currentPlayer == this->whitePlayer) ? blackPlayer : whitePlayer;
}

Player *Game::getWhitePlayer() const {
    return whitePlayer;
}

Player *Game::getBlackPlayer() const {
    return blackPlayer;
}

Player *Game::getCurrentPlayer() const {
    return currentPlayer;
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
    auto enPassant = (this->enPassantTargetPosition != nullptr) ? this->enPassantTargetPosition->toString() : "-";

    ss << board << " "
       << activePlayer << " "
       << castling << " "
       << enPassant << " "
       << this->halfmoveClock << " "
       << this->fullmoveNumber;

    return ss.str();
}

Piece *Game::getPiece(Position position) const {
    return this->getBoard()->getField(position)->getPiece();
}

Game Game::fromFEN(const std::string &fen) {
    auto elements = split(fen, ' ');

    auto board = Board::fromFEN(elements[0]);

    auto activePlayer = elements[1];
    if (activePlayer.size() != 1 || (activePlayer[0] != 'w' && activePlayer[0] != 'b')) {
        throw FenException("Invalid FEN representation of Game");
    }
    auto whitePlayer = new Player("Player One", Color::WHITE);
    auto blackPlayer = new Player("Player Two", Color::BLACK);
    auto currentPlayer = (activePlayer[0] == 'w') ? whitePlayer : blackPlayer;
    for (auto piece: board->getAllPieces()) {
        if (piece->getColor() == Color::WHITE) {
            whitePlayer->getPieces().push_back(piece);
        } else {
            blackPlayer->getPieces().push_back(piece);
        }
    }

    auto castling = elements[2];
    auto canWhiteKingsideCastle = castling.find('K') != -1;
    auto canWhiteQueensideCastle = castling.find('Q') != -1;
    auto canBlackKingsideCastle = castling.find('k') != -1;
    auto canBlackQueensideCastle = castling.find('q') != -1;

    auto enPassant = elements[3];
    Position *enPassantPosition = nullptr;
    if (!(enPassant.size() == 1 && enPassant[0] == '-') && enPassant.size() != 2) {
        throw FenException("Invalid FEN representation of Game");
    }

    if (enPassant.size() == 2) {
        auto pos = Position::fromString(enPassant);
        enPassantPosition = new Position(pos.getRow(), pos.getCol());
    }

    auto halfmoveClock = std::stoi(elements[4]);
    auto fullmoveNumber = std::stoi(elements[5]);

    auto game = Game(
            board,
            whitePlayer,
            blackPlayer,
            currentPlayer,
            canWhiteKingsideCastle,
            canWhiteQueensideCastle,
            canBlackKingsideCastle,
            canBlackQueensideCastle,
            enPassantPosition,
            halfmoveClock,
            fullmoveNumber
    );
    return game;
};

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
        currentPlayer(currentPlayer),
        canWhiteKingsideCastle(canWhiteKingsideCastle),
        canWhiteQueensideCastle(canWhiteQueensideCastle),
        canBlackKingsideCastle(canBlackKingsideCastle),
        canBlackQueensideCastle(canBlackQueensideCastle),
        enPassantTargetPosition(enPassantTarget),
        halfmoveClock(halfmoveClock),
        fullmoveNumber(fullmoveNumber) {}



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

std::vector<Move> Game::getLegalMovesFrom(Position position) const {
    //todo: castling out of check and through check
    auto piece = this->getPiece(position);
    if (piece == nullptr || piece->getColor() != currentPlayer->getColor())
        return {};

    auto pieceColor = piece->getColor();
    auto movesForPiece = getMovesFrom(position);
    movesForPiece.erase(
            std::remove_if(movesForPiece.begin(), movesForPiece.end(), [pieceColor, this](Move m) {
                auto deepCopy = this->afterMove(m);
                return deepCopy.isCheck(pieceColor);
            }),
            movesForPiece.end());

    return movesForPiece;
}

std::vector<Move> Game::getLegalMovesForPlayer(Player *player) const {
    std::vector<Move> moves = {};
    for (auto piece: player->getPieces()) {
        auto pieceMoves = getLegalMovesFrom(piece->getPosition());
        moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
    }
    return moves;
}

Pawn *Game::getEnPassantTargetPiece() const {
    if (enPassantTargetPosition == nullptr)
        return nullptr;

    int targetRow = enPassantTargetPosition->getRow();
    int targetCol = enPassantTargetPosition->getCol();
    int rowOffsetFromEPPosition = (currentPlayer == whitePlayer) ? -1 : 1;

    auto positionOfTargetPiece = Position(targetRow + rowOffsetFromEPPosition, targetCol);
    auto ePTargetPiece = dynamic_cast<Pawn *>(getPiece(positionOfTargetPiece));
    if (ePTargetPiece == nullptr)
        throw std::bad_cast();
    return ePTargetPiece;
}

void Game::refreshEnPassant() {
    auto oldEnPassantTarget = this->getEnPassantTargetPiece();
    oldEnPassantTarget->setIsEnPassantTarget(false);
    delete this->enPassantTargetPosition;
    this->enPassantTargetPosition = nullptr;
}

void Game::refreshCastlingPossibilites(const Move &move) {
    if (move.getPiece()->getType() == PieceType::KING) {
        if (move.getPiece()->getColor() == Color::WHITE) {
            canWhiteKingsideCastle = false;
            canWhiteQueensideCastle = false;
        } else {
            canBlackKingsideCastle = false;
            canBlackQueensideCastle = false;
        }

    } else if (move.getPiece()->getType() == PieceType::ROOK) {
        if (move.getPiece()->getColor() == Color::WHITE) {
            if (move.getFrom().getRow() == 1 && move.getFrom().getCol() == 1) {
                canWhiteQueensideCastle = false;
            } else if (move.getFrom().getRow() == 1 && move.getFrom().getCol() == 8) {
                canWhiteKingsideCastle = false;
            }
        } else {
            if (move.getFrom().getRow() == 8 && move.getFrom().getCol() == 1) {
                canBlackQueensideCastle = false;
            } else if (move.getFrom().getRow() == 8 && move.getFrom().getCol() == 8) {
                canBlackKingsideCastle = false;
            }
        }
    }
    if (move.isCapture() && move.getCapturedPiece()->getType() == PieceType::ROOK) {
        refreshCastlingAfterRookCapture(move.getCapturedPiece());
    }
}

void Game::refreshCastlingAfterRookCapture(const Piece *takenRook) {
    if (takenRook->getPosition() == Position(1, 1)) {
        canWhiteQueensideCastle = false;
    } else if (takenRook->getPosition() == Position(1, 8)) {
        canWhiteKingsideCastle = false;
    }
    if (takenRook->getPosition() == Position(8, 1)) {
        canBlackQueensideCastle = false;
    } else if (takenRook->getPosition() == Position(8, 8)) {
        canBlackKingsideCastle = false;
    }
}

bool Game::possibleKingsideCastlingThisRound() const {
    if (getCurrentPlayer()->getColor() == Color::WHITE && !canWhiteKingsideCastle ||
        getCurrentPlayer()->getColor() == Color::BLACK && !canBlackKingsideCastle) {
        return false;
    }
    int currentPlayerBackRank = (getCurrentPlayer()->getColor() == Color::WHITE) ? 1 : 8;
    auto kingSideRook = getPiece(Position(currentPlayerBackRank, 8));
    auto king = getPiece(Position(currentPlayerBackRank, 5));

    bool canCastle = (noPiecesBetweenKingAndRook(king, kingSideRook));
    return canCastle;
}

bool Game::possibleQueensideCastlingThisRound() const {
    if (getCurrentPlayer()->getColor() == Color::WHITE && !canWhiteQueensideCastle ||
        getCurrentPlayer()->getColor() == Color::BLACK && !canBlackQueensideCastle) {
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
    int castlingRank = (currentPlayer->getColor() == Color::WHITE) ? 1 : 8;
    auto fromPosition = Position(castlingRank, 5);
    auto toPosition = Position(castlingRank, 7);
    return Move(fromPosition, toPosition, getPiece(fromPosition), nullptr);
}

Move Game::generateQueenSideCastle() const {
    int castlingRank = (currentPlayer->getColor() == Color::WHITE) ? 1 : 8;
    auto fromPosition = Position(castlingRank, 5);
    auto toPosition = Position(castlingRank, 3);
    return Move(fromPosition, toPosition, getPiece(fromPosition), nullptr);
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

Game Game::afterMove(Move move) const {
    auto deepCopy = Game::fromFEN(this->toFEN());
    auto sourcePiece = deepCopy.getPiece(move.getFrom());

    Piece *takenPiece = (move.getCapturedPiece() == nullptr) ? nullptr : deepCopy.getPiece(
            move.getCapturedPiece()->getPosition());
    auto moveEquivalentForDeepCopy = Move(move.getFrom(), move.getTo(), sourcePiece, takenPiece);
    deepCopy.makeMove(moveEquivalentForDeepCopy);
    return deepCopy;
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