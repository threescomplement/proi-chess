set(CHESS_LIBRARY_SOURCES
        Game.cpp
        Board.cpp
        Field.cpp
        Player.cpp
        Move.cpp
        Position.cpp
        FENParser.cpp
        HistoryManager.cpp
        pieces/Piece.cpp
        pieces/Pawn.cpp
        pieces/Rook.cpp
        pieces/Knight.cpp
        pieces/King.cpp
        pieces/Queen.cpp
        pieces/Bishop.cpp GameOver.h GameState.cpp)


add_library(chess STATIC ${CHESS_LIBRARY_SOURCES})
target_include_directories(chess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

