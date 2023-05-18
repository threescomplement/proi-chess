#include "common.h"

bool ChessUnitTestCommon::in(const std::vector <Move> &vec, const Move &val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

bool ChessUnitTestCommon::containsAll(const std::vector <Move> &container, const std::vector <Move> &contained) {
    if (container.size() != contained.size()) {
        return false;
    }

    return std::all_of(
            contained.begin(),
            contained.end(),
            [container](Move const &move) { return in(container, move); }
    );
}
