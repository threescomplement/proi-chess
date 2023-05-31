#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Player.h"
#include "pieces/PieceType.h"
#include "ChessExceptions.h"
#include "pieces/Pawn.h"


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

bool Game::isCheck() const {
    return false;  // TODO
}

void Game::makeMove(Move move) {
    this->board->makeMove(move);

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
    if (piece == nullptr || piece->getColor() != currentPlayer->getColor()) {
        return {};
    }
    return piece->getMoves();
}

std::vector<Move> Game::getAllPlayerMoves(Player &player) const {
    std::vector<Move> moves = {};
    for (auto piece: player.getPieces()) {
        auto pieceMoves = piece->getMoves();
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