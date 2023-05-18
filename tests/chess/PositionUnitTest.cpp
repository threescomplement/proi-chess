#include "gtest/gtest.h"
#include "../../src/chess/Position.h"


namespace PositionUnitTest {
    TEST(Position, constructor) {
        auto position = Position(5, 8);
        ASSERT_EQ(5, position.getRow());
        ASSERT_EQ(8, position.getCol());
    }

    TEST(Position, constructorInvalidCoordinates) {
        ASSERT_THROW(Position(0, 4), std::invalid_argument);
        ASSERT_THROW(Position(1, 9), std::invalid_argument);
        ASSERT_THROW(Position(-1, 10), std::invalid_argument);
    }

    TEST(Position, toString) {
        ASSERT_EQ("h5", Position(5, 8).toString());
        ASSERT_EQ("a1", Position(1, 1).toString());
        ASSERT_EQ("e4", Position(4, 5).toString());
    }

    TEST(Position, fromString) {
        ASSERT_EQ(Position::fromString("h5"), Position(5, 8));
        ASSERT_EQ(Position::fromString("a1"), Position(1, 1));
        ASSERT_EQ(Position::fromString("e4"), Position(4, 5));
    }
}