cmake_minimum_required(VERSION 3.3)
project(DSV)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")

set(SOURCE_FILES dsv.cpp dsv.h)
add_library(DSV ${SOURCE_FILES})

add_subdirectory(lib/gtest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(dsv_tests test_dsv.cpp)
target_link_libraries(dsv_tests gtest gtest_main DSV)

add_test(NAME DSV-Test COMMAND dsv_tests)

set(DSV_HEADER_PATH ${PROJECT_SOURCE_DIR})
set(DSV_LIBRARY_PATH ${PROJECT_BINARY_DIR})
