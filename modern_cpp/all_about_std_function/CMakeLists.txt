project(All-about-Function)

set(CMAKE_CXX_STANDARD 14)

add_executable(fn function.cpp)

add_test(NAME Know-all-about-Functions
      COMMAND fn)
