set(GUI_SOURCES main.cpp)
add_executable(gui ${GUI_SOURCES})
target_link_libraries(gui
        chess
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
