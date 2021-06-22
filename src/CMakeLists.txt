set(SOURCE_FILES
	board.c
	commandline.c
	strategy.c)

add_library(${SRC_LIB} ${SOURCE_FILES})
target_include_directories(${SRC_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
