#include <vector>
#include "gtest/gtest.h"
#include "../../../src/chess/Move.h"
#include "../../../src/chess/Position.h"
#include "../../../src/chess/Board.h"
#include "../common.h"

#include "../../../src/chess/pieces/Rook.h"
using namespace ChessUnitTestCommon;

namespace RookUnitTest {
    TEST(Rook, getMoves_initialState) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto whiteRook = testBoard->getField(pos("a1"))->getPiece();
        auto blackRook = testBoard->getField(pos("h8"))->getPiece();
        auto whiteRookMoves = whiteRook->getMoves();
        auto blackRookMoves = blackRook->getMoves();
        ASSERT_EQ(whiteRookMoves.size(), blackRookMoves.size());
        ASSERT_EQ(whiteRookMoves.size(), 0);
    }

}