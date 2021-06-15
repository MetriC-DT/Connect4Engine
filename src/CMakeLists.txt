set(BINARY ${CMAKE_PROJECT_NAME})
set(SRC_LIB src.so)
set(SOURCE_FILES
	board.c
	commandline.c)

add_library(${SRC_LIB} ${SOURCE_FILES})
target_include_directories(${SRC_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${BINARY} main.c)
target_link_libraries(${BINARY} PUBLIC ${SRC_LIB})
