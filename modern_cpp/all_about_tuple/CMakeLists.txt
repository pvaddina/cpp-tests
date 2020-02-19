project(All-about-Tuple)

set(CMAKE_CXX_STANDARD 17)

add_executable(tupletest test.cpp)

add_test(NAME All-about-Tuple
      COMMAND tupletest)
