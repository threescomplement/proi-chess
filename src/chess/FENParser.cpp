#include "FENParser.h"
#include "Game.h"
#include "Board.h"
#include "Color.h"
#include "Player.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"

Game FENParser::parseGame(const std::string &fen) {
    auto elements = split(fen, ' ');

    auto board = FENParser::parseBoard(elements[0]);

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

    int halfmoveClock;
    try {
        halfmoveClock = std::stoi(elements[4]);
    } catch (std::exception &e) {
        throw FenException("Invalid FEN - halfmove clock value");
    }

    int fullmoveNumber;
    try {
        fullmoveNumber = std::stoi(elements[5]);
    } catch (std::exception &e) {
        throw FenException("Invalid FEN - fullmove number value");
    }

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
}

Board *FENParser::parseBoard(const std::string &fen) {
    auto board = Board::emptyBoard();

    int row = 8;
    int col = 1;

    for (auto character: fen) {
        if (isdigit(character)) {
            // empties
            std::string stringOfEmpties = {character};
            col += std::stoi(stringOfEmpties);

        } else if (character == '/') {
            // next row
            row -= 1;
            col = 1;
        } else {
            Piece *piece = nullptr;
            switch (character) {
                case 'p': {
                    piece = new Pawn(Color::BLACK, board->getField(Position(row, col)));
                    break;
                }
                case 'P': {
                    piece = new Pawn(Color::WHITE, board->getField(Position(row, col)));
                    break;
                }
                case 'r': {
                    piece = new Rook(Color::BLACK, board->getField(Position(row, col)));
                    break;
                }
                case 'R': {
                    piece = new Rook(Color::WHITE, board->getField(Position(row, col)));
                    break;
                }
                case 'n': {
                    piece = new Knight(Color::BLACK, board->getField(Position(row, col)));
                    break;
                }
                case 'N': {
                    piece = new Knight(Color::WHITE, board->getField(Position(row, col)));
                    break;
                }
                case 'b': {
                    piece = new Bishop(Color::BLACK, board->getField(Position(row, col)));
                    break;
                }
                case 'B': {
                    piece = new Bishop(Color::WHITE, board->getField(Position(row, col)));
                    break;
                }
                case 'q': {
                    piece = new Queen(Color::BLACK, board->getField(Position(row, col)));
                    break;
                }
                case 'Q': {
                    piece = new Queen(Color::WHITE, board->getField(Position(row, col)));
                    break;
                }
                case 'k': {
                    piece = new King(Color::BLACK, board->getField(Position(row, col)));
                    board->setBlackKing(piece);
                    break;
                }
                case 'K': {
                    piece = new King(Color::WHITE, board->getField(Position(row, col)));
                    board->setWhiteKing(piece);
                    break;
                }
                default:
                    throw FenException("Invalid FEN representation of Game");
            }
            board->getAllPieces().push_back(piece);
            board->getField(Position(row, col))->setPiece(piece);
            col += 1;
        }
    }
    return board;
}

std::string FENParser::toString(const Game &game) {
    std::stringstream ss;
    auto board = FENParser::toString(*game.getBoard());
    auto activePlayer = (game.getCurrentPlayer() == game.getWhitePlayer()) ? "w" : "b";
    auto castling = FENParser::castlingAvailability(game);
    auto enPassant = (game.getEnPassantTargetPosition() != nullptr)
                     ? game.getEnPassantTargetPosition()->toString()
                     : "-";

    ss << board << " "
       << activePlayer << " "
       << castling << " "
       << enPassant << " "
       << game.getHalfmoveClock() << " "
       << game.getFullmoveNumber();

    return ss.str();
}

std::string FENParser::toString(const Board &board) {
    std::stringstream ss;

    for (int row = BOARD_SIZE; row >= 1; row--) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            int empties = 0;
            auto tempCol = col;
            while (tempCol <= BOARD_SIZE && board.getField(Position(row, tempCol))->isEmpty()) {
                empties++;
                tempCol++;
            }
            if (empties == 0) {
                auto currPieceChar = board.getField(Position(row, col))->getPiece()->getCharacter();
                ss << currPieceChar;
            } else {
                ss << empties;
                col = col + empties - 1;
            }
        }
        ss << '/';
    }

    std::string result = ss.str();
    result = result.substr(0, result.size() - 1);
    return result;
}

std::string FENParser::castlingAvailability(const Game &game) {
    std::stringstream ss;
    if (game.getCanWhiteKingsideCastle()) {
        ss << "K";
    }
    if (game.getCanWhiteQueensideCastle()) {
        ss << "Q";
    }
    if (game.getCanBlackKingsideCastle()) {
        ss << "k";
    }
    if (game.getCanBlackQueensideCastle()) {
        ss << "q";
    }

    auto result = ss.str();
    if (result.empty()) {
        return "-";
    }

    return result;
}
