#include "Player.h"
#include "Color.h"

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
