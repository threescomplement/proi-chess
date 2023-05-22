#include "gtest/gtest.h"
#include "Player.h"
#include "Color.h"
#include "pieces/Pawn.h"

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
}