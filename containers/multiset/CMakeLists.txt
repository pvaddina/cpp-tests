project(Multiset)

set(CMAKE_CXX_STANDARD 17)

add_executable(mset multiset.cpp)

add_test(NAME Multiset-use-cases
      COMMAND mset)

