cmake_minimum_required(VERSION 3.5.1)

project(Normal)
add_executable(normal normal.cpp)

add_test(NAME "Normal"
        COMMAND normal)



