SET(BOT_SOURCES StockfishBot.cpp ChessBot.cpp)
add_library(bot ${BOT_SOURCES})
target_link_libraries(bot chess Qt::Core)
target_include_directories(bot INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})