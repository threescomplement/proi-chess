
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace PawnUnitTest {

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

    TEST(Pawn, getMoves_basePositionTwoMoves) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto testedPawn = testBoard->getField(Position(2, 5))->getPiece();
        auto movesForPawn = testedPawn->getMoves();
        ASSERT_EQ(movesForPawn.size(), 2);
        Move expectedMove1 = {Position(2, 5), Position(3, 5), testedPawn, false};
        Move expectedMove2 = {Position(2, 5), Position(4, 5), testedPawn, false};
        ASSERT_TRUE(in(movesForPawn, expectedMove1));
        ASSERT_TRUE(in(movesForPawn, expectedMove2));
    }


    TEST(Pawn, getMoves_twoAttacksPossible) {
        auto board = Board::fromFEN("rnbqkbnr/ppp1p1pp/8/3p1p2/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(Position(4, 5))->getPiece();
        auto pawnMoves = pawn->getMoves();

        auto expected = {
                Move({4, 5}, {5, 4}, pawn, true),
                Move({4, 5}, {5, 5}, pawn, false),
                Move({4, 5}, {5, 6}, pawn, true)
        };
        ASSERT_EQ(3, pawnMoves.size());
        ASSERT_TRUE(containsAll(pawnMoves, expected));
    }

    TEST(Pawn, getMoves_oneAttackPossible) {

    }

    TEST(Pawn, getMoves_attackOutOfBounds) {

    }

    TEST(Pawn, getMoves_fieldBehindAttackedProtected) {

    }

};