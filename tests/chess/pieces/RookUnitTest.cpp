#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Board.h"
#include "../common.h"
#include "FENParser.h"


using namespace ChessUnitTestCommon;

namespace RookUnitTest {
    TEST(Rook, getMoves_initialState) {
        auto testBoard = FENParser::parseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteRook = testBoard->getField(pos("a1"))->getPiece();
        auto blackRook = testBoard->getField(pos("h8"))->getPiece();
        auto whiteRookMoves = whiteRook->getMoves();
        auto blackRookMoves = blackRook->getMoves();
        ASSERT_EQ(whiteRookMoves.size(), blackRookMoves.size());
        ASSERT_EQ(whiteRookMoves.size(), 0);
    }

    TEST(Rook, getMovesMultipleDirectionsBlockedCapturesAndBoardBoundary) {
        auto board = FENParser::parseBoard("rnbqkbnr/1pppp3/p4ppp/8/P2R4/8/1PPPPPPP/1NBQKBNR");
        auto rook = board->getField(pos("d4"))->getPiece();
        auto moves = rook->getMoves();

        auto expected = {
                Move(pos("d4"), pos("d3"), rook),
                Move(pos("d4"), pos("b4"), rook),
                Move(pos("d4"), pos("c4"), rook),
                Move(pos("d4"), pos("e4"), rook),
                Move(pos("d4"), pos("f4"), rook),
                Move(pos("d4"), pos("g4"), rook),
                Move(pos("d4"), pos("h4"), rook),
                Move(pos("d4"), pos("d5"), rook),
                Move(pos("d4"), pos("d6"), rook),
                Move(pos("d4"), pos("d7"), rook, board->getField(pos("d7"))->getPiece()),
        };

        ASSERT_TRUE(isPermutation(moves, expected));
    }

}