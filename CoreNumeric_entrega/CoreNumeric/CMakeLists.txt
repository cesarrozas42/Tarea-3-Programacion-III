cmake_minimum_required(VERSION 3.20)
project(CoreNumeric LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(core_numeric INTERFACE)
target_include_directories(core_numeric INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_sum tests/test_sum.cpp)
target_link_libraries(test_sum PRIVATE core_numeric)

add_executable(test_mean tests/test_mean.cpp)
target_link_libraries(test_mean PRIVATE core_numeric)

add_executable(test_variance tests/test_variance.cpp)
target_link_libraries(test_variance PRIVATE core_numeric)

add_executable(test_max tests/test_max.cpp)
target_link_libraries(test_max PRIVATE core_numeric)

add_executable(test_transform_reduce tests/test_transform_reduce.cpp)
target_link_libraries(test_transform_reduce PRIVATE core_numeric)

add_executable(test_variadic tests/test_variadic.cpp)
target_link_libraries(test_variadic PRIVATE core_numeric)

add_executable(test_if_constexpr tests/test_if_constexpr.cpp)
target_link_libraries(test_if_constexpr PRIVATE core_numeric)
