set(CMAKE_AUTORCC ON)
set(GUI_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.ui
        sources.qrc
        clickable_label.cpp
        GameField.cpp
        GameField.h)

add_executable(gui ${GUI_SOURCES})
target_include_directories(gui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gui
        chess
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
