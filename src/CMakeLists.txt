set(SOURCE_FILES
	board.c
	commandline.c
	strategy.c)

add_library(${SRC_LIB} ${SOURCE_FILES})
target_include_directories(${SRC_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenMP REQUIRED)
target_link_libraries(${SRC_LIB} PRIVATE "${OpenMP_CXX_FLAGS}")
target_compile_options(${SRC_LIB} PRIVATE "${OpenMP_CXX_FLAGS}")
