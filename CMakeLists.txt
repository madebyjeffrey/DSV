cmake_minimum_required(VERSION 3.3)
project(DSV)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
elseif  ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fprofile-arcs -ftest-coverage")
endif()

set(SOURCE_FILES dsv.cpp dsv.h)
add_library(DSV ${SOURCE_FILES})
include_directories(include)
#add_subdirectory(lib/gtest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#add_executable(dsv_tests test_dsv.cpp)
#target_link_libraries(dsv_tests gtest gtest_main DSV)

#add_test(NAME DSV-Test COMMAND dsv_tests)

add_executable(dsv2_tests test_dsv2.cpp)
target_link_libraries(dsv2_tests)

add_test(NAME DSV2-Test COMMAND dsv2_tests)


set(DSV_HEADER_PATH ${PROJECT_SOURCE_DIR})
set(DSV_LIBRARY_PATH ${PROJECT_BINARY_DIR})
