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

add_executable(main ./src/main.cpp
        src/chess/Match.cpp
        src/chess/Match.h
        src/chess/Board.cpp
        src/chess/Board.h
        src/chess/Field.cpp
        src/chess/Field.h
        src/chess/Player.cpp
        src/chess/Player.h
        src/chess/Move.cpp
        src/chess/Move.h
        src/chess/Color.h
        src/chess/Piece.cpp
        src/chess/Piece.h
        src/chess/Position.cpp
        src/chess/Position.h
        src/chess/PieceType.h
        src/chess/pieces/Pawn.cpp
        src/chess/pieces/Pawn.h
        src/chess/pieces/Rook.cpp
        src/chess/pieces/Rook.h
        src/chess/pieces/Knight.cpp
        src/chess/pieces/Knight.h
        src/chess/pieces/King.cpp
        src/chess/pieces/King.h
        src/chess/pieces/Queen.cpp
        src/chess/pieces/Queen.h
        src/chess/pieces/Bishop.cpp
        src/chess/pieces/Bishop.h)

add_executable(test ./tests/test.cpp)
target_link_libraries(test PUBLIC gtest_main)