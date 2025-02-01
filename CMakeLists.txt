cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(LogSystem)

add_library(LogSystem include/LogSystem.hpp LogSystem.cpp)

target_include_directories(LogSystem PUBLIC include)