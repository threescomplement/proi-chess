//
// Created by mGarbowski on 12.05.2023.
//
#include "gtest/gtest.h"
#include "../../src/chess/Move.h"
#include "../../src/chess/pieces/Knight.h"
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/pieces/Queen.h"

namespace MoveUnitTest {
    TEST(Move, constructor) {
        auto knight = new Knight(Color::WHITE, nullptr, nullptr);
        auto move = Move(Position(8, 2), Position(6, 3), knight, false);
        ASSERT_EQ(Position(8, 2), move.getFrom());
        ASSERT_EQ(Position(6, 3), move.getTo());
        ASSERT_EQ(knight, move.getPiece());
        ASSERT_EQ(false, move.getIsCapture());
    }

    TEST(Move, toStringFigure) {
        auto move = Move(Position(8, 2), Position(6, 3), new Knight(Color::WHITE, nullptr, nullptr), false);
        ASSERT_EQ("Nc6", move.toString());
    }

    TEST(Move, toStringPawn) {
        auto move = Move(Position(2, 4), Position(4, 4), new Pawn(Color::WHITE, nullptr, nullptr), false);
        ASSERT_EQ("d4", move.toString());
    }

    TEST(Move, toStringFigureCapture) {
        auto move = Move(Position(3, 2), Position(6, 5), new Queen(Color::WHITE, nullptr, nullptr), true);
        ASSERT_EQ("Qxe6", move.toString());
    }

    TEST(Move, toStringPawnCapture) {
        auto move = Move(Position(7, 2), Position(8, 1), new Pawn(Color::WHITE, nullptr, nullptr), true);
        ASSERT_EQ("bxa8", move.toString());
    }
}