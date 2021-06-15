set(BINARY ${CMAKE_PROJECT_NAME}_tests)
set(SUITES_LIB suites.so)
set(SOURCE_FILES board_suite.c)

find_library(CUNIT_LIB cunit)

add_library(${SUITES_LIB} ${SOURCE_FILES})
target_include_directories(${SUITES_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${BINARY} tests.c)
target_link_libraries(${BINARY} PUBLIC ${CUNIT_LIB})
target_link_libraries(${BINARY} PUBLIC ${SRC_LIB} ${SUITES_LIB})

add_test(NAME ${BINARY} COMMAND ${BINARY})
