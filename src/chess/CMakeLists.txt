add_library(chess STATIC
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
        pieces/Bishop.cpp
        )
target_include_directories(chess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})