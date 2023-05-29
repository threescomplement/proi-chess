#include "gtest/gtest.h"
#include "../../src/chess/Move.h"
#include "../../src/chess/pieces/Knight.h"
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/pieces/Queen.h"
#include "../../src/chess/Color.h"

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
}