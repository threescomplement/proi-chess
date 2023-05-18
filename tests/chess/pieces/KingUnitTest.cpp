
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
                Move(pos("h2"), pos("h1"), whiteKing, false),
                Move(pos("h2"), pos("h3"), whiteKing, false),
                Move(pos("h2"), pos("g1"), whiteKing, false),
                Move(pos("h2"), pos("g2"), whiteKing, false),
                Move(pos("h2"), pos("g3"), whiteKing, false)
        };
        std::vector<Move> expectedBlackMoves = {
                Move(pos("a6"), pos("a5"), blackKing, false),
                Move(pos("a6"), pos("a4"), blackKing, false),
                Move(pos("a6"), pos("b5"), blackKing, false),
                Move(pos("a6"), pos("b4"), blackKing, false),
                Move(pos("a6"), pos("b3"), blackKing, false),
        };
        
        ASSERT_TRUE(isPermutation(expectedWhiteMoves, whitekingMoves));
        ASSERT_TRUE(isPermutation(expectedBlackMoves, blackKingMoves));
    }

    TEST(King, onEdgeRank) {

    }

    TEST(King, possibleCaptures) {

    }
}
