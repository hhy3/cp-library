cmake_minimum_required(VERSION 3.16)
project(hy LANGUAGES CXX)

add_library(hy INTERFACE)
target_include_directories(hy INTERFACE .)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_executable(template template.cc)
target_link_libraries(template hy)
