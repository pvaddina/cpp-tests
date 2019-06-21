cmake_minimum_required(VERSION 3.5.1)
project(CPP-Tests)

include_directories(inc)

add_subdirectory(algos)
add_subdirectory(curious_recursive)
add_subdirectory(gen)
add_subdirectory(modern_cpp)
add_subdirectory(concurrency)
add_subdirectory(patterns)
add_subdirectory(traits)
add_subdirectory(typelists)
add_subdirectory(utils)

