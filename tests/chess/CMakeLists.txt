set(CHESS_UNIT_TEST_SOURCES
        common.cpp
        MoveUnitTest.cpp
        PositionUnitTest.cpp
        FieldUnitTest.cpp
        GameUnitTest.cpp
        BoardUnitTest.cpp
        pieces/PawnUnitTest.cpp
        pieces/KingUnitTest.cpp
        pieces/KnightUnitTests.cpp
        pieces/QueenUnitTest.cpp
        pieces/BishopUnitTest.cpp
        pieces/RookUnitTest.cpp PlayerUnitTest.cpp FENParserUnitTest.cpp)

add_executable(all-unit-tests ${CHESS_UNIT_TEST_SOURCES})
target_link_libraries(all-unit-tests PUBLIC gtest_main chess)
target_include_directories(all-unit-tests INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})