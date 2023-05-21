#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include <string>

class Move;

class Position;

namespace ChessUnitTestCommon {
    template<class T>
    bool in(const std::vector<T> &vec, const T &val);

    template<class T>
    bool isPermutation(const std::vector<T> &container, const std::vector<T> &contained);

    Position pos(const std::string &textRepr);
}
#endif //CHESS_COMMON_H
