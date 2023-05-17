#ifndef CHESS_COMMON_H
#define CHESS_COMMON_H

#include <vector>
#include <algorithm>
#include "../../src/chess/Move.h"

namespace ChessUnitTestCommon {
    bool in(const std::vector<Move> &vec, const Move &val) {
        return std::find(vec.begin(), vec.end(), val) != vec.end();
    }

    bool containsAll(std::vector<Move> const &container, std::vector<Move> const &contained) {
        if (container.size() != contained.size()) {
            return false;
        }

        return std::all_of(
                contained.begin(),
                contained.end(),
                [container](Move const &move) { return in(container, move); }
        );
    }
}
#endif //CHESS_COMMON_H
