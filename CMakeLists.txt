cmake_minimum_required(VERSION 3.10.0)
project(Atcoder VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Atcoder CSES/DP/1158.cpp)

target_compile_features(Atcoder PUBLIC cxx_std_23)