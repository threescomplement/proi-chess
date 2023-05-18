#include "../common.h"
#include "../../../src/chess/pieces/Pawn.h"
#include "../../../src/chess/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace ChessUnitTestCommon;

namespace PawnUnitTest {

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
        ASSERT_TRUE(isPermutation(pawnMoves, expected));
    }


    TEST(Pawn, getMoves_singleMovePossible) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppppp/8/p7/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(Position(4, 5))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {Move(Position(4, 5), Position(5, 5), pawn, false)};
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, getMoves_oneAttackPossible) {
        auto board = Board::fromFEN("rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(Position(4, 5))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {
                Move(Position(4, 5), Position(5, 5), pawn, false),
                Move(Position(4, 5), Position(5, 6), pawn, true),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, getmoves_fieldBehindAttackedProtected) {
        auto board = Board::fromFEN("rnbqkbnr/pp2pppp/2p5/3p4/3PP3/8/PPP2PPP/RNBQKBNR");
        auto pawn = board->getField(pos("e4"))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {
                Move(pos("e4"), pos("e5"), pawn, false),
                Move(pos("e4"), pos("d5"), pawn, true)
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }


};