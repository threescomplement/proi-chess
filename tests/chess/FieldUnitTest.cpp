#include "gtest/gtest.h"
#include "Field.h"

namespace FieldUnitTest {
    TEST(Field, constructor) {
        auto field = Field(Position(1, 1));
        ASSERT_EQ(nullptr, field.getPiece());
        ASSERT_EQ(Position(1, 1), field.getPosition());
        ASSERT_EQ(nullptr, field.getBoard());
    }
}