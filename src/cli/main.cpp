#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Game.h"
#include "Color.h"
#include "Player.h"
#include "Move.h"
#include "Board.h"
#include "Position.h"


std::string playerPrompt(const Game &game) {
    return (game.getCurrentPlayer()->getColor() == Color::WHITE)
           ? "White move > "
           : "Black move > ";
}

Move parseMove(const std::string& moveStr, const Game &game) {
    if (moveStr.size() != 4) {
        throw std::invalid_argument("Invalid representation of a move");
    }

    Position sourcePosition = Position::fromString(moveStr.substr(0, 2));
    Position targetPosition = Position::fromString(moveStr.substr(2, 2));
    auto movedPiece = game.getPiece(sourcePosition);
    auto capturedPiece = game.getPiece(targetPosition);

    if (game.getCurrentPlayer()->getColor() != movedPiece->getColor()) {
        throw std::invalid_argument("Player can only move his own piece");
    }

    return {sourcePosition, targetPosition, movedPiece, capturedPiece};
}

int main(int argc, char *argv[]) {
    auto game = Game();

    while (true) {
        std::cout  << game.getBoard()->toString() << std::endl;
        std::string moveStr;
        std::cout << playerPrompt(game);

        try {
            std::cin >> moveStr;
            auto move = parseMove(moveStr, game);
            auto availableMoves = game.getMovesFrom(move.getFrom());
            if (std::find(availableMoves.begin(), availableMoves.end(), move) == availableMoves.end()) {
                throw std::invalid_argument("Illegal move");
            }

            game.makeMove(move);
        } catch (std::exception &e) {
            std::cout << "Cannot make move " << moveStr << std::endl;
            continue;
        }
    }

    // TODO: use appropriate exceptions
    // TODO: handle exceptions and print more helpful messages


    return 0;
}
