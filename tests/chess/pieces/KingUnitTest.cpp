
#include "gtest/gtest.h"
#include "../../../src/chess/pieces/King.h"
#include "../../../tests/chess/common.h"
#include "../../../src/chess/Board.h"
using namespace ChessUnitTestCommon;

namespace KingUnitTest {
    TEST(King, noPossibleMoves) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteKing = testBoard->getField(pos("e1"))->getPiece();
        auto blackKing = testBoard->getField(pos("e1"))->getPiece();
        auto whitekingMoves = whiteKing->getMoves();
        auto blackKingMoves = blackKing->getMoves();
        ASSERT_EQ(whitekingMoves.size(), blackKingMoves.size());
        ASSERT_EQ(whitekingMoves.size(), 0);
    }

    TEST(King, onEdgeFile) {
        auto testBoard = Board::fromFEN("8/8/k7/8/8/8/7K/8");
        auto whiteKing = testBoard->getField(pos("h2"))->getPiece();
        auto blackKing = testBoard->getField(pos("a6"))->getPiece();
        auto whitekingMoves = whiteKing->getMoves();
        auto blackKingMoves = blackKing->getMoves();
        std::vector<Move> expectedWhiteMoves = {
                Move(pos("h2"), pos("h1"), whiteKing),
                Move(pos("h2"), pos("h3"), whiteKing),
                Move(pos("h2"), pos("g1"), whiteKing),
                Move(pos("h2"), pos("g2"), whiteKing),
                Move(pos("h2"), pos("g3"), whiteKing)
        };
        std::vector<Move> expectedBlackMoves = {
                Move(pos("a6"), pos("a5"), blackKing),
                Move(pos("a6"), pos("a7"), blackKing),
                Move(pos("a6"), pos("b5"), blackKing),
                Move(pos("a6"), pos("b7"), blackKing),
                Move(pos("a6"), pos("b6"), blackKing),
        };

        ASSERT_TRUE(isPermutation(expectedWhiteMoves, whitekingMoves));
        ASSERT_TRUE(isPermutation(expectedBlackMoves, blackKingMoves));
    }

    TEST(King, onEdgeRank) {
        auto testBoard = Board::fromFEN("3k4/8/8/8/8/8/8/7K");
        auto whiteKing = testBoard->getField(pos("h1"))->getPiece();
        auto blackKing = testBoard->getField(pos("d8"))->getPiece();
        auto whitekingMoves = whiteKing->getMoves();
        auto blackKingMoves = blackKing->getMoves();
        std::vector<Move> expectedWhiteMoves = {
                Move(pos("h1"), pos("h2"), whiteKing),
                Move(pos("h1"), pos("g1"), whiteKing),
                Move(pos("h1"), pos("g2"), whiteKing)
        };
        std::vector<Move> expectedBlackMoves = {
                Move(pos("d8"), pos("d7"), blackKing),
                Move(pos("d8"), pos("c8"), blackKing),
                Move(pos("d8"), pos("e8"), blackKing),
                Move(pos("d8"), pos("c7"), blackKing),
                Move(pos("d8"), pos("e7"), blackKing),
        };

        ASSERT_TRUE(isPermutation(expectedWhiteMoves, whitekingMoves));
        ASSERT_TRUE(isPermutation(expectedBlackMoves, blackKingMoves));
    }

    TEST(King, possibleCaptures) {
        auto testBoard = Board::fromFEN("8/8/8/8/8/8/2K2P1P/6k1");
        auto blackKing = testBoard->getField(pos("g1"))->getPiece();
        auto blackKingMoves = blackKing->getMoves();

        std::vector<Move> expectedBlackMoves = {
                Move(pos("g1"), pos("f2"), blackKing, testBoard->getField(pos("f2"))->getPiece()),
                Move(pos("g1"), pos("h2"), blackKing, testBoard->getField(pos("h2"))->getPiece()),
                Move(pos("g1"), pos("g2"), blackKing),
                Move(pos("g1"), pos("h1"), blackKing),
                Move(pos("g1"), pos("f1"), blackKing)
        };

        ASSERT_TRUE(isPermutation(expectedBlackMoves, blackKingMoves));
    }
}
