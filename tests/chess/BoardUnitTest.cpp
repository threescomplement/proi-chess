#include "gtest/gtest.h"
#include "../../src/chess/Board.h"
#include "../../src/chess/Color.h"
#include "ChessExceptions.h"
#include "FENParser.h"
#include "common.h"

using namespace ChessUnitTestCommon;

namespace BoardUnitTest {
    TEST(Board, constructorInitializesEmptyBoard) {
        auto board = Board();
        ASSERT_EQ("8/8/8/8/8/8/8/8", FENParser::toString(board));
    }

    TEST(Board, startingBoard) {
        auto board = Board::startingBoard();
        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", FENParser::toString(*board));
    }

    TEST(Board, makeMoveNoCapture) {
        auto board = Board::startingBoard();
        auto pawn = board->getField(pos("e2"))->getPiece();
        auto move = Move(pos("e2"), pos("e4"), pawn);

        board->makeMove(move);

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR", FENParser::toString(*board));

        ASSERT_EQ(pos("e4"), pawn->getPosition());
        ASSERT_EQ(board->getField(pos("e4")), pawn->getField());
        ASSERT_EQ(pawn, board->getField(pos("e4"))->getPiece());

        ASSERT_TRUE(board->getField(pos("e2"))->isEmpty());
        ASSERT_FALSE(board->getField(pos("e4"))->isEmpty());
    }

    TEST(Board, makeMoveFromEmptyField) {
        auto board = Board::startingBoard();
        auto pawn = board->getField(pos("e2"))->getPiece();
        auto move = Move(pos("e4"), pos("e5"), pawn);

        ASSERT_THROW(board->makeMove(move), IllegalMoveException);
    }

    TEST(Board, makeMoveCapturePieceOfSameColor) {
        auto board = Board::startingBoard();
        auto knight = board->getField(pos("g1"))->getPiece();
        auto move = Move(pos("g1"), pos("e2"), knight);

        ASSERT_THROW(board->makeMove(move), IllegalMoveException);
    }

    TEST(Board, makeMoveCapture) {
        auto board = FENParser::parseBoard("rnbqkbnr/pppp1ppp/8/4p3/8/5N2/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(pos("f3"))->getPiece();
        auto pawn = board->getField(pos("e5"))->getPiece();
        auto move = Move(pos("f3"), pos("e5"), knight, pawn);

        board->makeMove(move);

        ASSERT_EQ("rnbqkbnr/pppp1ppp/8/4N3/8/8/PPPPPPPP/RNBQKB1R", FENParser::toString(*board));

        ASSERT_EQ(pos("e5"), knight->getPosition());
        ASSERT_EQ(knight, board->getField(pos("e5"))->getPiece());
        ASSERT_EQ(board->getField(pos("e5")), knight->getField());

        ASSERT_THROW(pawn->getPosition(), PieceNotOnBoardException);
        ASSERT_EQ(nullptr, board->getField(pos("f3"))->getPiece());
        ASSERT_EQ(nullptr, pawn->getField());


        ASSERT_TRUE(board->getField(pos("f3"))->isEmpty());
        ASSERT_FALSE(board->getField(pos("e5"))->isEmpty());
    }
}

