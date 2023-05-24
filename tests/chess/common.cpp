#include "common.h"
#include "../../src/chess/Position.h"
#include "../../src/chess/Move.h"

template<class T>
bool ChessUnitTestCommon::in(const std::vector<T> &vec, const T &val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

bool ChessUnitTestCommon::in(const std::vector<Piece*> &vec, Piece *val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

bool ChessUnitTestCommon::isPermutation(const std::vector<Move> &vectorA, const std::vector<Move> &vectorB) {
    if (vectorA.size() != vectorB.size()) {
        return false;
    }

    return std::all_of(
            vectorB.begin(),
            vectorB.end(),
            [vectorA](Move const &element) { return in(vectorA, element); }
    );
}

Position ChessUnitTestCommon::pos(const std::string &textRepr) {
    return Position::fromString(textRepr);
}
