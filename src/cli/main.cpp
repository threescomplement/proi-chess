#include <iostream>
#include <algorithm>
#include "Game.h"
#include "Color.h"
#include "Player.h"
#include "Move.h"
#include "Board.h"
#include "Position.h"
#include "ChessExceptions.h"
#include "CLIExceptions.h"
#include "StockfishBot.h"


std::string playerPrompt(const Game &game) {
    return (game.getCurrentPlayer()->getColor() == Color::WHITE)
           ? "White move > "
           : "Black move > ";
}

Move parseMove(const std::string &moveStr, const Game &game) {
    if (moveStr.size() != 4) {
        throw InvalidPlayerInputException("Invalid representation of a move");
    }

    Position sourcePosition = Position::fromString(moveStr.substr(0, 2));
    Position targetPosition = Position::fromString(moveStr.substr(2, 2));
    auto movedPiece = game.getPiece(sourcePosition);
    auto capturedPiece = game.getPiece(targetPosition);

    if (movedPiece == nullptr) {
        throw InvalidPlayerInputException("Cannot move from empty field");
    }

    if (game.getCurrentPlayer()->getColor() != movedPiece->getColor()) {
        throw InvalidPlayerInputException("Player can only move his own piece");
    }

    return {sourcePosition, targetPosition, movedPiece, capturedPiece};
}

void processPlayerTurn(Game &game) {
    while (true) {
        std::cout << game.getBoard()->toString() << std::endl;
        std::string moveStr;
        std::cout << playerPrompt(game);

        try {
            std::cin >> moveStr;
            auto move = parseMove(moveStr, game);
            auto availableMoves = game.getMovesFrom(move.getFrom());

            if (std::find(availableMoves.begin(), availableMoves.end(), move) == availableMoves.end()) {
                std::cout << "Illegal move " << moveStr
                          << ", moves allowed from " << move.getFrom().toString() << ":" << std::endl;

                for (auto availableMove: availableMoves) {
                    std::cout << availableMove.toStockfishNotation() << " ";
                }
                std::cout << std::endl;
                continue;
            }

            game.makeMove(move);
            break;

        } catch (const ChessException &e) {
            std::cout << moveStr << ": " << e.what() << std::endl;
            continue;
        } catch (const CLIException &e) {
            std::cout << moveStr << ": " << e.what() << std::endl;
            continue;
        } catch (const std::exception &e) {
            std::cout << moveStr << ": cannot make move " << e.what() << std::endl;
        }
    }
}

void processBotTurn(Game &game, StockfishBot &bot) {
    game.makeMove(bot.getBestNextMove());
}

void playPlayerVersusPlayer() {
    auto game = Game();

    while (true) {
        processPlayerTurn(game);
    }
}

void playPlayerVersusComputer() {
    auto game = Game();
    auto bot = StockfishBot(game);
    Color botColor;

    while (true) {
        std::string choice;
        std::cout << "Choose color (w/b): ";
        std::cin >> choice;

        if (choice[0] == 'w') {
            botColor = Color::BLACK;
            break;
        } else if (choice[0] == 'b') {
            botColor = Color::WHITE;
            break;
        } else {
            std::cout << "Invalid choice, type either 'b' or 'w'" << std::endl;
            continue;
        }
    }

    while (true) {
        if (game.getCurrentPlayer()->getColor() == botColor) {
            processBotTurn(game, bot);
        } else {
            processPlayerTurn(game);
        }
    }
}

int main(int argc, char *argv[]) {
    while (true) {
        std::string choice;
        std::cout << "1. Play against another player on the same keyboard" << std::endl;
        std::cout << "2. Play against computer" << std::endl;
        std::cout << "(1/2) > ";
        std::cin >> choice;

        if (choice[0] == '1') {
            playPlayerVersusPlayer();
        } else if (choice[0] == '2') {
            playPlayerVersusComputer();
        } else {
            std::cout << "Invalid command, choose either '1' or '2'" << std::endl;
            continue;
        }
    }

    // TODO: help command
    // TODO: give up command
    // TODO: handle end of game
    // TODO: load from FEN

    return 0;
}
