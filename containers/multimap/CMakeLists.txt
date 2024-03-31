project(Multimap)

set(CMAKE_CXX_STANDARD 17)

add_executable(mmap multimap.cpp)

add_test(NAME Multimap-use-cases
      COMMAND mmap)

