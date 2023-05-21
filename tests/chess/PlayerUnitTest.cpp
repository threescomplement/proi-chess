#include "gtest/gtest.h"
#include "Player.h"
#include "Color.h"
#include "pieces/Pawn.h"

namespace PlayerUnitTest {
    TEST(Player, constructor) {
        auto player = Player("Player");

        ASSERT_EQ("Player", player.getName());
        ASSERT_EQ(0, player.getPieces().size());
    }

    TEST(Player, doesNotDeletePieces) {
        auto player = new Player("Player");
        auto pawn = new Pawn(Color::WHITE, nullptr);
        player->getPieces().push_back(pawn);
        delete player;

        ASSERT_NE(nullptr, pawn);
    }
}