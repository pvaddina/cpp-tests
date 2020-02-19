project(All-about-Default-Methods)

set(CMAKE_CXX_STANDARD 11)

add_executable(default main.cpp)

add_test(NAME Know-all-about-Defaulted-Methods
      COMMAND default)

