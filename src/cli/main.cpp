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

int main(int argc, char *argv[]) {
    auto game = Game();

    while (true) {
        std::cout << game.getBoard()->toString() << std::endl;
        std::string moveStr;
        std::cout << playerPrompt(game);

        try {
            std::cin >> moveStr;
            auto move = parseMove(moveStr, game);
            auto availableMoves = game.getMovesFrom(move.getFrom());
            if (std::find(availableMoves.begin(), availableMoves.end(), move) == availableMoves.end()) {
                throw IllegalMoveException("Move not allowed");
            }

            game.makeMove(move);
        } catch (const std::exception &e) {
            std::cout << "Cannot make move: " << moveStr << " " << e.what() << std::endl;
            continue;
        }
    }

    // TODO: handle exceptions and print more helpful messages


    return 0;
}
