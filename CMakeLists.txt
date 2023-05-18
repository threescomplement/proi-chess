cmake_minimum_required(VERSION 3.16)
project(chess)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(CHESS_LIBRARY_SOURCES
        src/chess/Game.h
        src/chess/Game.cpp
        src/chess/Board.h
        src/chess/Board.cpp
        src/chess/Field.h
        src/chess/Field.cpp
        src/chess/Player.h
        src/chess/Player.cpp
        src/chess/Move.h
        src/chess/Move.cpp
        src/chess/Color.h
        src/chess/Position.h
        src/chess/Position.cpp
        src/chess/pieces/Piece.h
        src/chess/pieces/Piece.cpp
        src/chess/pieces/Pawn.h
        src/chess/pieces/Pawn.cpp
        src/chess/pieces/Rook.h
        src/chess/pieces/Rook.cpp
        src/chess/pieces/Knight.h
        src/chess/pieces/Knight.cpp
        src/chess/pieces/King.h
        src/chess/pieces/King.cpp
        src/chess/pieces/Queen.h
        src/chess/pieces/Queen.cpp
        src/chess/pieces/Bishop.h
        src/chess/pieces/Bishop.cpp
        src/chess/pieces/BasePiece.cpp src/chess/pieces/BasePiece.h)

set(CHESS_UNIT_TEST_SOURCES
        tests/chess/common.h
        tests/chess/common.cpp
        tests/chess/MoveUnitTest.cpp
        tests/chess/PositionUnitTest.cpp
        tests/chess/FieldUnitTest.cpp
        tests/chess/GameTest.cpp
        tests/chess/BoardUnitTest.cpp
        tests/chess/pieces/PawnUnitTest.cpp
        tests/chess/pieces/KingUnitTest.cpp
        tests/chess/pieces/KnightUnitTests.cpp
        tests/chess/pieces/QueenUnitTest.cpp
        tests/chess/pieces/BishopUnitTest.cpp
        tests/chess/pieces/RookUnitTest.cpp)

set(BOT_UNIT_TEST_SOURCES
        ./tests/bot/test.cpp
        )

add_executable(gui ./src/gui/main.cpp ${CHESS_LIBRARY_SOURCES})
add_executable(cli ./src/cli/main.cpp ${CHESS_LIBRARY_SOURCES})

add_executable(all-unit-tests
        ${CHESS_UNIT_TEST_SOURCES}
        ${CHESS_LIBRARY_SOURCES}
        ${BOT_LIBRARY_SOURCES}
        ${BOT_UNIT_TEST_SOURCES}
        )
target_link_libraries(all-unit-tests PUBLIC gtest_main)