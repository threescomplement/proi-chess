#include "common.h"
#include "../../src/chess/Position.h"
#include "../../src/chess/Move.h"

template<class T>
bool ChessUnitTestCommon::in(const std::vector <T> &vec, const T &val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

template<class T>
bool ChessUnitTestCommon::isPermutation(const std::vector <T> &container, const std::vector <T> &contained) {
    if (container.size() != contained.size()) {
        return false;
    }

    return std::all_of(
            contained.begin(),
            contained.end(),
            [container](T const &element) { return in(container, element); }
    );
}

Position ChessUnitTestCommon::pos(const std::string &textRepr) {
    return Position::fromString(textRepr);
}
