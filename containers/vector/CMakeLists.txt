project(Vectors)

set(CMAKE_CXX_STANDARD 17)

add_executable(vector vec.cpp)

add_test(NAME Vector-use-cases
      COMMAND vector)

