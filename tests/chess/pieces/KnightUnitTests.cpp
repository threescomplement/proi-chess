#include "gtest/gtest.h"
#include "../common.h"
#include "../../../src/chess/Board.h"

using namespace ChessUnitTestCommon;
namespace KnightUnitTests {
    TEST(Knight, getMovesStartingPosition) {
        auto board = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

        auto whiteKnight = board->getField(pos("g1"))->getPiece();
        auto whiteMoves = whiteKnight->getMoves();
        auto whiteExpected = {
                Move(pos("g1"), pos("f3"), whiteKnight, false),
                Move(pos("g1"), pos("h3"), whiteKnight, false),
        };

        auto blackKnight = board->getField(pos("b8"))->getPiece();
        auto blackMoves = blackKnight->getMoves();
        auto blackExpected = {
                Move(pos("b8"), pos("a6"), blackKnight, false),
                Move(pos("b8"), pos("c6"), blackKnight, false),
        };


        ASSERT_TRUE(isPermutation(whiteMoves, whiteExpected));
        ASSERT_TRUE(isPermutation(blackMoves, blackExpected));
    }

    TEST(Knight, getMovesMultiplePossibleNoCapture) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppppp/p7/8/8/5N2/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(pos("f3"))->getPiece();
        auto moves = knight->getMoves();

        auto expected = {
                Move(pos("f3"), pos("g1"), knight, false),
                Move(pos("f3"), pos("d4"), knight, false),
                Move(pos("f3"), pos("e5"), knight, false),
                Move(pos("f3"), pos("g5"), knight, false),
                Move(pos("f3"), pos("h4"), knight, false),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Knight, getMovesMultipleCaptures) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppp1p/p5p1/4N3/8/8/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(pos("e5"))->getPiece();
        auto moves = knight->getMoves();

        auto expected = {
                Move(pos("e5"), pos("d3"), knight, false),
                Move(pos("e5"), pos("f3"), knight, false),
                Move(pos("e5"), pos("g4"), knight, false),
                Move(pos("e5"), pos("g6"), knight, true),
                Move(pos("e5"), pos("f7"), knight, true),
                Move(pos("e5"), pos("d7"), knight, true),
                Move(pos("e5"), pos("c6"), knight, false),
                Move(pos("e5"), pos("c4"), knight, false),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }
}