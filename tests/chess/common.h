#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include <string>

class Board;
class Move;
class Piece;
class Game;
class Position;

namespace ChessUnitTestCommon {
    template<class T>
    bool in(const std::vector<T> &vec, const T &val);

    bool in(const std::vector<Piece*> &vec, Piece *val);

    bool isPermutation(const std::vector<Move> &vectorA, const std::vector<Move> &vectorB);

    Position pos(const std::string &textRepr);

    Game fenGame(const std::string &fen);

    Board *fenBoard(const std::string &fen);

    std::string fen(const Game &game);

    std::string fen(const Board &board);

    std::string fen(Board *board);
}
#endif //CHESS_COMMON_H
