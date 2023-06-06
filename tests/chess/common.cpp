#include "common.h"
#include "Position.h"
#include "Game.h"
#include "FENParser.h"
#include "Move.h"

template<class T>
bool ChessUnitTestCommon::in(const std::vector<T> &vec, const T &val) {
    return std::find(vec.begin(), vec.end(), val) != vec.end();
}

bool ChessUnitTestCommon::in(const std::vector<Piece *> &vec, Piece *val) {
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

std::string ChessUnitTestCommon::fen(const Game &game) {
    return FENParser::gameToString(game);
}

std::string ChessUnitTestCommon::fen(const Board &board) {
    return FENParser::boardToString(board);
}

std::string ChessUnitTestCommon::fen(Board *board) {
    return FENParser::boardToString(*board);
}

Game ChessUnitTestCommon::fenGame(const std::string &fen) {
    return FENParser::parseGame(fen);
}

Board *ChessUnitTestCommon::fenBoard(const std::string &fen) {
    return FENParser::parseBoard(fen);
}

