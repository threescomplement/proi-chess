cmake_minimum_required(VERSION 3.16)
project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# This can be either set manually (terrible solution)
# set(CMAKE_PREFIX_PATH "/home/mgarbowski/Qt/6.5.0/gcc_64")
#
# Or you can add Qt installation directory do PATH environment variable on your machine
# execute this in bash
# export PATH="~/Qt/6.5.0/gcc_64/:$PATH"

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

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
        )

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

set(GUI_SOURCES src/gui/main.cpp)

add_executable(cli ./src/cli/main.cpp ${CHESS_LIBRARY_SOURCES})

add_executable(all-unit-tests
        ${CHESS_UNIT_TEST_SOURCES}
        ${CHESS_LIBRARY_SOURCES}
        ${BOT_LIBRARY_SOURCES}
        ${BOT_UNIT_TEST_SOURCES}
        )
target_link_libraries(all-unit-tests PUBLIC gtest_main)



add_executable(gui ${GUI_SOURCES})
target_link_libraries(gui
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
