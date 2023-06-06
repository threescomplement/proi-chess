#include "gtest/gtest.h"
#include "Move.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "pieces/Queen.h"
#include "Color.h"
#include "Game.h"
#include "common.h"

using namespace ChessUnitTestCommon;

namespace MoveUnitTest {
    TEST(Move, constructorNoCaptureImplicit) {
        auto knight = new Knight(Color::WHITE, nullptr);
        auto move = Move(Position(8, 2), Position(6, 3), knight);

        ASSERT_EQ(Position(8, 2), move.getFrom());
        ASSERT_EQ(Position(6, 3), move.getTo());
        ASSERT_EQ(knight, move.getPiece());
        ASSERT_EQ(nullptr, move.getCapturedPiece());
        ASSERT_EQ(false, move.isCapture());
    }

    TEST(Move, constructorNoCaptureExplicit) {
        auto knight = new Knight(Color::WHITE, nullptr);
        auto move = Move(Position(8, 2), Position(6, 3), knight, nullptr);

        ASSERT_EQ(Position(8, 2), move.getFrom());
        ASSERT_EQ(Position(6, 3), move.getTo());
        ASSERT_EQ(knight, move.getPiece());
        ASSERT_EQ(nullptr, move.getCapturedPiece());
        ASSERT_EQ(false, move.isCapture());
    }

    TEST(Move, constructorCapture) {
        auto knight = new Knight(Color::WHITE, nullptr);
        auto pawn = new Pawn(Color::BLACK, nullptr);
        auto move = Move(Position(8, 2), Position(6, 3), knight, pawn);

        ASSERT_EQ(Position(8, 2), move.getFrom());
        ASSERT_EQ(Position(6, 3), move.getTo());
        ASSERT_EQ(knight, move.getPiece());
        ASSERT_EQ(pawn, move.getCapturedPiece());
        ASSERT_EQ(true, move.isCapture());
    }


    TEST(Move, toStringFigure) {
        auto move = Move(Position(8, 2), Position(6, 3), new Knight(Color::WHITE, nullptr));
        ASSERT_EQ("Nc6", move.toString());
    }

    TEST(Move, toStringPawn) {
        auto move = Move(Position(2, 4), Position(4, 4), new Pawn(Color::WHITE, nullptr));
        ASSERT_EQ("d4", move.toString());
    }

    TEST(Move, toStringFigureCapture) {
        auto move = Move(Position(3, 2), Position(6, 5), new Queen(Color::WHITE, nullptr),
                         new Pawn(Color::BLACK, nullptr));
        ASSERT_EQ("Qxe6", move.toString());
    }

    TEST(Move, toStringPawnCapture) {
        auto move = Move(Position(7, 2), Position(8, 1), new Pawn(Color::WHITE, nullptr),
                         new Queen(Color::BLACK, nullptr));
        ASSERT_EQ("bxa8", move.toString());
    }

    TEST(Move, parseSmithNotationPromotion) {
        auto game = fenGame("rnbqkb1r/pppp2Pp/4pp1n/8/7p/8/PPPPPP2/RNBQKBNR w KQkq - 0 6");
        auto move = Move::parseSmithNotation("g7g8q", game);
        ASSERT_EQ(pos("g7"), move.getFrom());
        ASSERT_EQ(pos("g8"), move.getTo());
        ASSERT_EQ(game.getPiece(pos("g7")), move.getPiece());
        ASSERT_EQ(nullptr, move.getCapturedPiece());
        ASSERT_EQ(PieceType::QUEEN, move.getPromoteTo());
    }

    TEST(Move, parseSmithNotationNoPromotion) {
        auto game = Game();
        auto move = Move::parseSmithNotation("e2e4", game);
        ASSERT_EQ(pos("e2"), move.getFrom());
        ASSERT_EQ(pos("e4"), move.getTo());
        ASSERT_EQ(game.getPiece(pos("e2")), move.getPiece());
        ASSERT_EQ(nullptr, move.getCapturedPiece());
        ASSERT_EQ(PieceType::NONE, move.getPromoteTo());
    }

    TEST(Move, fromPositionsEnPassantCapture) {
        auto game = fenGame("rnbqkbnr/ppppp1p1/7p/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
        auto move = Move::fromPositions(game, pos("e5"), pos("f6"));
        ASSERT_EQ(pos("e5"), move.getFrom());
        ASSERT_EQ(pos("f6"), move.getTo());
        ASSERT_EQ(game.getPiece(pos("e5")), move.getPiece());
        ASSERT_EQ(game.getPiece(pos("f5")), move.getCapturedPiece());
        ASSERT_EQ(PieceType::NONE, move.getPromoteTo());
    }
}