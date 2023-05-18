#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include "../../src/chess/Move.h"

namespace ChessUnitTestCommon {
    bool in(const std::vector<Move> &vec, const Move &val);

    bool containsAll(std::vector<Move> const &container, std::vector<Move> const &contained);
}
#endif //CHESS_COMMON_H
