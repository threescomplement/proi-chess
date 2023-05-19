set(CHESS_UNIT_TEST_SOURCES
        ../../tests/chess/common.h
        ../../tests/chess/common.cpp
        ../../tests/chess/MoveUnitTest.cpp
        ../../tests/chess/PositionUnitTest.cpp
        ../../tests/chess/FieldUnitTest.cpp
        ../../tests/chess/GameTest.cpp
        ../../tests/chess/BoardUnitTest.cpp
        ../../tests/chess/pieces/PawnUnitTest.cpp
        ../../tests/chess/pieces/KingUnitTest.cpp
        ../../tests/chess/pieces/KnightUnitTests.cpp
        ../../tests/chess/pieces/QueenUnitTest.cpp
        ../../tests/chess/pieces/BishopUnitTest.cpp
        ../../tests/chess/pieces/RookUnitTest.cpp)

set(CHESS_LIBRARY_SOURCES
        Game.cpp
        Board.cpp
        Field.cpp
        Player.cpp
        Move.cpp
        Position.cpp
        pieces/Piece.cpp
        pieces/Pawn.cpp
        pieces/Rook.cpp
        pieces/Knight.cpp
        pieces/King.cpp
        pieces/Queen.cpp
        pieces/Bishop.cpp)


add_library(chess STATIC ${CHESS_LIBRARY_SOURCES})
target_include_directories(chess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(all-unit-tests
        ${CHESS_UNIT_TEST_SOURCES}
        )
target_link_libraries(all-unit-tests PUBLIC gtest_main chess)