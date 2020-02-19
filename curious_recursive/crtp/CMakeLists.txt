cmake_minimum_required(VERSION 3.5.1)

project(CRTP)
add_executable(crtp crtp.cpp)

add_test(NAME "CRTP"
         COMMAND crtp)

