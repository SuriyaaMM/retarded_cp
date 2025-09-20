cmake_minimum_required(VERSION 3.10.0)
project(Atcoder VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Atcoder test.cpp)

target_compile_features(Atcoder PUBLIC cxx_std_20)
target_compile_options(Atcoder PRIVATE -Wall -Wextra)
