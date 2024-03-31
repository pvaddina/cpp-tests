project(Array_Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(array array.cpp)

add_test(NAME Array-use-cases
      COMMAND array)

