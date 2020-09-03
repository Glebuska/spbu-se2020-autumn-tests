cmake_minimum_required(VERSION 3.16.3)
project(tests)

set(CMAKE_C_STANDARD 99)

set_property(SOURCE sort.s PROPERTY LANGUAGE C)

configure_file(test_1.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(/usr/local/include)
find_library(CMOCKA_LIBRARY libcmocka.so.0)

set_source_files_properties(main.c
        PROPERTIES
        COMPILE_DEFINITIONS
        UNIT_TESTING)

add_executable(program main_test.c main.c sort.s sort.h config.h)

add_test(calculator_test calculator_test)

target_link_libraries(program ${CMOCKA_LIBRARY})