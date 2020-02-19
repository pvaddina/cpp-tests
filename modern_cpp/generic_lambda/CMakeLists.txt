project(Generic-Lambdas)

set(CMAKE_CXX_STANDARD 14)

add_executable(genlambda main.cpp)

add_test(NAME All-about-Generic-lambdas
      COMMAND genlambda)

