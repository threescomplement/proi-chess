/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>

class Piece;
enum class Color;


/**
 * Player is not responsible for freeing memory related to his Pieces
 */
class Player {
private:
    std::string name;
    Color color;
    std::vector<Piece *> pieces;
public:
    Player(std::string name, Color color);

    ~Player() = default;

    std::string const &getName() const;

    Color getColor() const;

    std::vector<Piece *> &getPieces();

    void removePiece(Piece *piece);
};


#endif //CHESS_PLAYER_H
