cmake_minimum_required(VERSION 3.2)

project(difftool C CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -O2)

add_executable(difftool difftool.cc)

install(TARGETS difftool DESTINATION bin)
