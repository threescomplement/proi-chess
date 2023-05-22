#include <algorithm>
#include "Player.h"
#include "Color.h"
#include "exceptions/PieceNotOnBoardException.h"

Player::Player(std::string name, Color color) {
    this->name = name;
    this->color = color;
    this->pieces = {};
}

std::string const &Player::getName() const {
    return name;
}

std::vector<Piece *> &Player::getPieces() {
    return pieces;
}

Color Player::getColor() const {
    return color;
}

void Player::removePiece(Piece *piece) {
    auto it = std::find(pieces.begin(), pieces.end(), piece);
    if (it == pieces.end()) {
        throw PieceNotOnBoardException("The eplayer does not have this piece");
    }

    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece));
}
