project(All-about-Aliases)

set(CMAKE_CXX_STANDARD 11)

add_executable(alias alias.cpp)

add_test(NAME Know-all-about-Aliases
      COMMAND alias)
