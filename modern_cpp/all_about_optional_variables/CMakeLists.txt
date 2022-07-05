project(All-about-Aliases)

set(CMAKE_CXX_STANDARD 17)

add_executable(optional main.cpp)

add_test(NAME Know-all-about-Optional
      COMMAND optional)
