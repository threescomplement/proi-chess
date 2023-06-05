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
#include "pieces/Pawn.h"


bool handleIfSpecialCommand(const std::string &playerInput) {
    if (playerInput == "help") {
        std::cout << "Type the move you want to make in Smith notation" << std::endl;
        std::cout << "eg. to move from e2 to e4 simply type 'e2e4', no need to specify the piece type" << std::endl;
        return true;
    }

    return false;
}

std::string playerPrompt(const Game &game) {
    return (game.getCurrentPlayer()->getColor() == Color::WHITE)
           ? "White move > "
           : "Black move > ";
}


void processPlayerTurn(Game &game) {
    while (true) {
        std::cout << game.getBoard()->toString() << std::endl;
        std::string moveStr;
        std::cout << playerPrompt(game);
        std::cin >> moveStr;

        if (handleIfSpecialCommand(moveStr)) {
            continue;
        }

        try {
            auto move = Move::parseStockfishNotation(moveStr, game);
            auto availableMoves = game.getMovesFrom(move.getFrom());

            if (std::find(availableMoves.begin(), availableMoves.end(), move) == availableMoves.end()) {
                std::cout << "Illegal move " << moveStr
                          << ", moves allowed from " << move.getFrom().toString() << ":" << std::endl;

                for (auto availableMove: availableMoves) {
                    std::cout << availableMove.toSmithNotation() << " ";
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

void processBotTurn(Game &game, ChessBot &bot) {
    game.makeMove(bot.getBestNextMove());
}

void playPlayerVersusPlayer(Game &game) {
    while (true) {
        processPlayerTurn(game);
    }
}

void playPlayerVersusComputer(Game &game) {
    ChessBot &bot = *new StockfishBot(game);
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

Game initiateGame(int argc, char *argv[]) {
    if (argc == 2) {
        std::string fen = argv[1];
        return Game::fromFEN(fen);
    }
    return {};
}

int main(int argc, char *argv[]) {
    Game game = initiateGame(argc, argv);

    while (true) {
        std::string choice;
        std::cout << "1. Play against another player on the same keyboard" << std::endl;
        std::cout << "2. Play against computer" << std::endl;
        std::cout << "(1/2) > ";
        std::cin >> choice;

        if (choice[0] == '1') {
            playPlayerVersusPlayer(game);
        } else if (choice[0] == '2') {
            playPlayerVersusComputer(game);
        } else {
            std::cout << "Invalid command, choose either '1' or '2'" << std::endl;
            continue;
        }
    }

    // TODO: give up command
    // TODO: handle end of game

    return 0;
}
