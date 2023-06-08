/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "ChessBot.h"

int ChessBot::getDepth() const {
    return depth;
}

void ChessBot::setDepth(int depth) {
    ChessBot::depth = depth;
}
