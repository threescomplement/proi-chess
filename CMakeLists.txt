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

set(CHESS_LIBRARRY_SOURCES
        src/chess/Game.h
        src/chess/Board.h
        src/chess/Field.h
        src/chess/Player.h
        src/chess/Move.h
        src/chess/Color.h
        src/chess/pieces/Piece.h
        src/chess/Position.h
        src/chess/pieces/Pawn.h
        src/chess/pieces/Rook.h
        src/chess/pieces/Knight.h
        src/chess/pieces/King.h
        src/chess/pieces/Queen.h
        src/chess/pieces/Bishop.h
        )

set(CHESS_UNIT_TEST_SOURCES
        ./tests/chess/test.cpp
        )

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