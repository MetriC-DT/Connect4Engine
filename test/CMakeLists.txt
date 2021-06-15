set(TEST_BIN tests)
set(SUITES_LIB suites.so)
set(SUITES_SRC board_suite.c)

find_library(CUNIT_LIB cunit)

add_library(${SUITES_LIB} ${SUITES_SRC})
target_link_libraries(${SUITES_LIB} ${SRC_LIB})

add_executable(${TEST_BIN} tests.c)
target_link_libraries(${TEST_BIN} ${CUNIT_LIB})
target_link_libraries(${TEST_BIN} ${SRC_LIB} ${SUITES_LIB})

add_test(NAME ${TEST_BIN} COMMAND ${TEST_BIN})
