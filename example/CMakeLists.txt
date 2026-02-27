cmake_minimum_required(VERSION 3.10)
project(smaut_example C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccan)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

enable_testing()

add_executable(test_do_division
    test_do_division.c 
    do_division.c 
    ccan/ccan/tap/tap.c
    ../smaut.c
)

target_link_options(test_do_division PRIVATE LINKER:--wrap,__assert_fail)

add_test(NAME test_do_division COMMAND test_do_division)
