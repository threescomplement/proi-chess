
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

namespace PawnUnitTest {

    bool in(const std::vector<Move> &vec,const Move &val) {
        return std::find(vec.begin(), vec.end(), val) != vec.end();
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

    }

    TEST(Pawn, getMoves_oneAttackPossible) {

    }

    TEST(Pawn, getMoves_attackOutOfBounds) {

    }

    TEST(Pawn, getMoves_fieldBehindAttackedProtected)
    {

    }

};