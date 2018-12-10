cmake_minimum_required(VERSION 2.7)
project(EndGame C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

add_definitions("-fPIC -Wall")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions("-DDEBUG=1 -g -O0 ")
endif()

subdirs(sylvan)

include_directories(src)
include_directories(sylvan/src)
link_directories(sylvan/src)

add_executable(endgame
    src/main.cpp
)

target_link_libraries(endgame sylvan)

ADD_CUSTOM_TARGET (distclean)

ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -rf *.dSYM */*.dSYM Makefile */Makefile */CMakeFiles CMakeFiles CMakeCache.txt Makefile */Makefile  */CMakeCache.txt cmake_install.cmake */cmake_install.cmake
    TARGET  distclean
)
