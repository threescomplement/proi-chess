#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->pieces = {};
}

std::string const &Player::getName() const {
    return name;
}

std::vector<Piece *> &Player::getPieces() {
    return pieces;
}
