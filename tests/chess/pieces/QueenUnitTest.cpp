#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Position.h"
#include "../../../src/chess/Board.h"
#include "../common.h"

#include "../../../src/chess/pieces/Queen.h"
using namespace ChessUnitTestCommon;

namespace QueenUnitTest {
    TEST(Queen, getMoves_initialState) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteQueen = testBoard->getField(pos("d1"))->getPiece();
        auto blackQueen = testBoard->getField(pos("d8"))->getPiece();
        auto whiteQueenMoves = whiteQueen->getMoves();
        auto blackQueenMoves = blackQueen->getMoves();
        ASSERT_EQ(whiteQueenMoves.size(), blackQueenMoves.size());
        ASSERT_EQ(whiteQueenMoves.size(), 0);
    }
}