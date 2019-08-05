cmake_minimum_required(VERSION 3.10)
project(capacitance_clamp)

include(CTest)
include_directories("${PROJECT_SOURCE_DIR}")
set(capacitance_clamp_module_source_files capacitance_clamp_lib.cpp capacitance_clamp_lib.h)
add_library(capacitance_clamp_library ${capacitance_clamp_module_source_files})

add_subdirectory(tests)

set(CMAKE_CTEST_COMMAND ctest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS tests_run)

enable_testing()
add_test(NAME CapacitanceClampLibraryTest COMMAND tests_run)