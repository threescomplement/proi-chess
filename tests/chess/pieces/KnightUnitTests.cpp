#include "gtest/gtest.h"
#include "../common.h"
#include "../../../src/chess/Board.h"

using namespace ChessUnitTestCommon;
namespace KnightUnitTests {
    TEST(Knight, getMovesStartingPosition) {
        auto board = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

        auto whiteKnight = board->getField(Position::fromString("g1"))->getPiece();
        auto whiteMoves = whiteKnight->getMoves();
        auto whiteExpected = {
                Move(Position::fromString("g1"), Position::fromString("f3"), whiteKnight, false),
                Move(Position::fromString("g1"), Position::fromString("h3"), whiteKnight, false),
        };

        auto blackKnight = board->getField(Position::fromString("b8"))->getPiece();
        auto blackMoves = blackKnight->getMoves();
        auto blackExpected = {
                Move(Position::fromString("b8"), Position::fromString("a6"), blackKnight, false),
                Move(Position::fromString("b8"), Position::fromString("c6"), blackKnight, false),
        };


        ASSERT_TRUE(isPermutation(whiteMoves, whiteExpected));
        ASSERT_TRUE(isPermutation(blackMoves, blackExpected));
    }

    TEST(Knight, getMovesMultiplePossibleNoCapture) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppppp/p7/8/8/5N2/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(Position::fromString("f3"))->getPiece();
        auto moves = knight->getMoves();

        auto expected = {
                Move(Position::fromString("f3"), Position::fromString("g1"), knight, false),
                Move(Position::fromString("f3"), Position::fromString("d4"), knight, false),
                Move(Position::fromString("f3"), Position::fromString("e5"), knight, false),
                Move(Position::fromString("f3"), Position::fromString("g5"), knight, false),
                Move(Position::fromString("f3"), Position::fromString("h4"), knight, false),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Knight, getMovesMultipleCaptures) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppp1p/p5p1/4N3/8/8/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(Position::fromString("e5"))->getPiece();
        auto moves = knight->getMoves();

        auto expected = {
                Move(Position::fromString("e5"), Position::fromString("d3"), knight, false),
                Move(Position::fromString("e5"), Position::fromString("f3"), knight, false),
                Move(Position::fromString("e5"), Position::fromString("g4"), knight, false),
                Move(Position::fromString("e5"), Position::fromString("g6"), knight, true),
                Move(Position::fromString("e5"), Position::fromString("f7"), knight, true),
                Move(Position::fromString("e5"), Position::fromString("d7"), knight, true),
                Move(Position::fromString("e5"), Position::fromString("c6"), knight, false),
                Move(Position::fromString("e5"), Position::fromString("c4"), knight, false),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }
}