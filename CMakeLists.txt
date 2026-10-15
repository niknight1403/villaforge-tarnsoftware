cmake_minimum_required(VERSION 3.16)
project(AOCS_EW_PerformanceTest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_performance
    src/optimized_pipeline.cpp
    tests/test_performance.cpp
)

target_include_directories(test_performance PRIVATE src)

enable_testing()
add_test(NAME PerformanceAndCostOptimizationTest COMMAND test_performance)
