#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include <string>

class Move;
class Piece;

class Position;

namespace ChessUnitTestCommon {
    template<class T>
    bool in(const std::vector<T> &vec, const T &val);

    bool in(const std::vector<Piece*> &vec, Piece *val);

    bool isPermutation(const std::vector<Move> &vectorA, const std::vector<Move> &vectorB);

    Position pos(const std::string &textRepr);
}
#endif //CHESS_COMMON_H
