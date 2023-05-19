SET(CLI_SOURCES main.cpp)
add_executable(cli ${CLI_SOURCES})
target_link_libraries(cli chess)