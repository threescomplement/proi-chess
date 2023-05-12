#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->pieces = {};
    this->isChecked = false;
}

