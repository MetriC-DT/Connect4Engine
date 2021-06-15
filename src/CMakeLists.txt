add_library(Board_lib board.c)
add_executable(Connect4Engine main.c)
target_link_libraries(Connect4Engine Board_lib)
