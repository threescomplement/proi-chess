#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Position.h"
#include "../../../src/chess/Board.h"
#include "../common.h"

#include "../../../src/chess/pieces/Bishop.h"
#include "FENParser.h"

using namespace ChessUnitTestCommon;

namespace BishopUnitTest {
    TEST(Bishop, getMoves_initialState) {
        auto testBoard = FENParser::parseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteBishop = testBoard->getField(pos("c1"))->getPiece();
        auto blackBishop = testBoard->getField(pos("f8"))->getPiece();
        auto whiteBishopMoves = whiteBishop->getMoves();
        auto blackBishopMoves = blackBishop->getMoves();
        ASSERT_EQ(whiteBishopMoves.size(), blackBishopMoves.size());
        ASSERT_EQ(whiteBishopMoves.size(), 0);
    }

    TEST(Bishop, oneDiagonalOpen) {
        auto testBoard = FENParser::parseBoard("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR");
        auto whiteBishop = testBoard->getField(pos("f1"))->getPiece();
        auto blackBishop = testBoard->getField(pos("c8"))->getPiece();
        auto whiteBishopMoves = whiteBishop->getMoves();
        auto blackBishopMoves = blackBishop->getMoves();

        std::vector<Move> expectedWhiteMoves = {
                Move(pos("f1"), pos("e2"), whiteBishop),
                Move(pos("f1"), pos("d3"), whiteBishop),
                Move(pos("f1"), pos("c4"), whiteBishop),
                Move(pos("f1"), pos("b5"), whiteBishop),
                Move(pos("f1"), pos("a6"), whiteBishop)
        };

        std::vector<Move> expectedBlackMoves = {
                Move(pos("c8"), pos("d7"), blackBishop),
                Move(pos("c8"), pos("e6"), blackBishop),
                Move(pos("c8"), pos("f5"), blackBishop),
                Move(pos("c8"), pos("g4"), blackBishop),
                Move(pos("c8"), pos("h3"), blackBishop)
        };

        ASSERT_EQ(whiteBishopMoves.size(), blackBishopMoves.size());
        ASSERT_EQ(whiteBishopMoves.size(), 5);
        ASSERT_TRUE(isPermutation(whiteBishopMoves, expectedWhiteMoves));
        ASSERT_TRUE(isPermutation(blackBishopMoves, expectedBlackMoves));
    }

    TEST(Bishop, bothDiagonalsCompletelyOpen) {
        auto testBoard = FENParser::parseBoard("5k2/8/4b3/8/8/4B3/8/1K6");
        auto whiteBishop = testBoard->getField(pos("e3"))->getPiece();
        auto blackBishop = testBoard->getField(pos("e6"))->getPiece();
        auto whiteBishopMoves = whiteBishop->getMoves();
        auto blackBishopMoves = blackBishop->getMoves();
        std::vector<Move> expectedWhiteMoves = {
                Move(pos("e3"), pos("c1"), whiteBishop),
                Move(pos("e3"), pos("d2"), whiteBishop),
                Move(pos("e3"), pos("f4"), whiteBishop),
                Move(pos("e3"), pos("g5"), whiteBishop),
                Move(pos("e3"), pos("h6"), whiteBishop),
                Move(pos("e3"), pos("a7"), whiteBishop),
                Move(pos("e3"), pos("b6"), whiteBishop),
                Move(pos("e3"), pos("c5"), whiteBishop),
                Move(pos("e3"), pos("d4"), whiteBishop),
                Move(pos("e3"), pos("f2"), whiteBishop),
                Move(pos("e3"), pos("g1"), whiteBishop)
        };

        std::vector<Move> expectedBlackMoves = {
                Move(pos("e6"), pos("c8"), blackBishop),
                Move(pos("e6"), pos("d7"), blackBishop),
                Move(pos("e6"), pos("f5"), blackBishop),
                Move(pos("e6"), pos("g4"), blackBishop),
                Move(pos("e6"), pos("h3"), blackBishop),
                Move(pos("e6"), pos("a2"), blackBishop),
                Move(pos("e6"), pos("b3"), blackBishop),
                Move(pos("e6"), pos("c4"), blackBishop),
                Move(pos("e6"), pos("d5"), blackBishop),
                Move(pos("e6"), pos("f7"), blackBishop),
                Move(pos("e6"), pos("g8"), blackBishop),
        };

        ASSERT_EQ(whiteBishopMoves.size(), blackBishopMoves.size());
        ASSERT_EQ(whiteBishopMoves.size(), 11);
        ASSERT_TRUE(isPermutation(whiteBishopMoves, expectedWhiteMoves));
        ASSERT_TRUE(isPermutation(blackBishopMoves, expectedBlackMoves));
    }

    TEST(Bishop, capturesAndOwnPiecesInTheWay) {
        auto testBoard = FENParser::parseBoard("5k2/8/8/8/5r2/4B3/3P4/1K6");
        auto whiteBishop = testBoard->getField(pos("e3"))->getPiece();
        auto whiteBishopMoves = whiteBishop->getMoves();
        std::vector<Move> expectedWhiteMoves = {
                Move(pos("e3"), pos("g1"), whiteBishop),
                Move(pos("e3"), pos("f2"), whiteBishop),
                Move(pos("e3"), pos("d4"), whiteBishop),
                Move(pos("e3"), pos("c5"), whiteBishop),
                Move(pos("e3"), pos("b6"), whiteBishop),
                Move(pos("e3"), pos("a7"), whiteBishop),
                Move(pos("e3"), pos("f4"), whiteBishop, testBoard->getField(pos("f4"))->getPiece()),
        };
        ASSERT_TRUE(isPermutation(whiteBishopMoves, expectedWhiteMoves));
    }
}