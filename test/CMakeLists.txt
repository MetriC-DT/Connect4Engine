set (TEST_EXECUTABLE UnitTests)
set (CMAKE_C_FLAGS "-Wall -Wextra -Werror")
find_library (CUNIT_LIB cunit)

add_executable(${TEST_EXECUTABLE} tests.c)

add_test(NAME ${TEST_EXECUTABLE} COMMAND ${TEST_EXECUTABLE})
target_link_libraries(${TEST_EXECUTABLE} PUBLIC Board_lib cunit)
