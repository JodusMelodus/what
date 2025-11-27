cmake_minimum_required(VERSION 3.16)
project(what C)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include_directories(include)

file(GLOB LIB_SOURCES "src/*.c")
add_library(what ${LIB_SOURCES})

add_executable(test_what tests/test_what.c)
target_link_libraries(test_what what)

include(CTest)
add_test(NAME what_test COMMAND test_what)
