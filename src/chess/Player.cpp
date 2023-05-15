#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->pieces = {};
    this->isChecked = false;
}

std::vector<Piece *> &Player::getPieces() {
    return pieces;
}

Player::Player()=default;
