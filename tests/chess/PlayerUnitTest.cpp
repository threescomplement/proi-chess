/*
 * Copyright (c) 2023.
 * Maksym Bieńkowski
 * Mikołaj Garbowski
 * Michał Łuszczek
 */

#include "gtest/gtest.h"
#include "Player.h"
#include "Color.h"
#include "pieces/Pawn.h"
#include "pieces/Rook.h"
#include "common.h"

using namespace ChessUnitTestCommon;

namespace PlayerUnitTest {
    TEST(Player, constructor) {
        auto player = Player("Player", Color::WHITE);

        ASSERT_EQ("Player", player.getName());
        ASSERT_EQ(Color::WHITE, player.getColor());
        ASSERT_EQ(0, player.getPieces().size());
    }

    TEST(Player, doesNotDeletePieces) {
        auto player = new Player("Player", Color::BLACK);
        auto pawn = new Pawn(Color::BLACK, nullptr);
        player->getPieces().push_back(pawn);
        delete player;

        ASSERT_NE(nullptr, pawn);
    }

    TEST(Player, removePiece) {
        auto player = Player("Player", Color::WHITE);
        auto pawn1 = new Pawn(Color::WHITE, nullptr);
        auto pawn2 = new Pawn(Color::WHITE, nullptr);
        auto pawn3 = new Pawn(Color::WHITE, nullptr);
        auto rook = new Rook(Color::WHITE, nullptr);

        player.getPieces().push_back(pawn1);
        player.getPieces().push_back(pawn2);
        player.getPieces().push_back(pawn3);
        player.getPieces().push_back(rook);
        ASSERT_EQ(4, player.getPieces().size());

        player.removePiece(pawn2);
        ASSERT_EQ(3, player.getPieces().size());
        ASSERT_TRUE(in(player.getPieces(), pawn1));
        ASSERT_FALSE(in(player.getPieces(), pawn2));
        ASSERT_TRUE(in(player.getPieces(), pawn3));
        ASSERT_TRUE(in(player.getPieces(), rook));;
    }
}