cmake_minimum_required(VERSION 3.20)
project(MemoryManagement VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Cache)
enable_testing()
add_subdirectory(Test)