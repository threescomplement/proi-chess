#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Position.h"
#include "../../../src/chess/Board.h"
#include "../common.h"

#include "../../../src/chess/pieces/Bishop.h"
using namespace ChessUnitTestCommon;

namespace BishopUnitTest {
    TEST(Bishop, getMoves_initialState) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteBishop = testBoard->getField(pos("c1"))->getPiece();
        auto blackBishop = testBoard->getField(pos("f8"))->getPiece();
        auto whiteBishopMoves = whiteBishop->getMoves();
        auto blackBishopMoves = blackBishop->getMoves();
        ASSERT_EQ(whiteBishopMoves.size(), blackBishopMoves.size());
        ASSERT_EQ(whiteBishopMoves.size(), 0);
    }


}