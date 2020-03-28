add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch)

set(SOURCE_LOCATION_TEST_SOURCES
    source_location_tests.cpp
)

find_program(MEMORYCHECK_COMMAND valgrind)

set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --verbose --error-exitcode=1")

add_executable(source_location.ut ${SOURCE_LOCATION_TEST_SOURCES})

target_link_libraries(source_location.ut PUBLIC Catch nostd::source_location)

add_test(NAME source_location_tests COMMAND source_location.ut)