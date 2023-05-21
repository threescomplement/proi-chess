set(GUI_SOURCES main.cpp mainwindow.cpp mainwindow.h
        mainwindow.ui
        sources.qrc)
set(CMAKE_AUTORCC ON)
add_executable(gui ${GUI_SOURCES})
target_link_libraries(gui
        chess
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
