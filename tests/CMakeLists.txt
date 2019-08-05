Project(tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests_run CapacitanceClampTest.cpp)

target_link_libraries(tests_run capacitance_clamp_library)
target_link_libraries(tests_run gtest gtest_main)
