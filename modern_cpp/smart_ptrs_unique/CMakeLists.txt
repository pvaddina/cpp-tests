cmake_minimum_required(VERSION 3.5)

project(Smart-Pointers-Tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(unique main.cpp)

add_test(NAME UniqueTests
      COMMAND unique)

