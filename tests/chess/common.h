#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include <string>

class Move;
class Position;

namespace ChessUnitTestCommon {
    bool in(const std::vector<Move> &vec, const Move &val);

    bool isPermutation(const std::vector<Move> &container, const std::vector<Move> &contained);

    Position pos(const std::string &textRepr);
}
#endif //CHESS_COMMON_H
