cmake_minimum_required(VERSION 3.26)
project(da2324_p02_sol)

set(CMAKE_CXX_STANDARD 14)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(TP2)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(da2324_p02_sol
        TP2/ex1.cpp
        TP2/ex2.cpp
        TP2/ex3.cpp
        TP2/ex4.cpp
        TP2/ex5.cpp
)

target_link_libraries(da2324_p02_sol gtest gtest_main)