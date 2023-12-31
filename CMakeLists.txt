cmake_minimum_required(VERSION 3.16)
project(chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# This can be either set manually (terrible solution)
# set(CMAKE_PREFIX_PATH "~/Qt/6.5.0/gcc_64")
#
# Or you can add Qt installation directory do PATH environment variable on your machine
# execute this in bash
# export PATH="~/Qt/6.5.0/gcc_64/:$PATH"
#
# Or add to CMake options in CLion
# -DQt6_DIR:PATH=~/Qt/6.5.0/gcc_64/lib/cmake/Qt6

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


add_subdirectory(src/chess)
add_subdirectory(src/bot)
add_subdirectory(src/gui)
add_subdirectory(src/cli)
add_subdirectory(tests/chess)
