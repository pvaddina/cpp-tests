project(Copy-and-Move-Operations)

set(CMAKE_CXX_STANDARD 11)

add_executable(copy_move cp_mv.cpp)

add_test(NAME Examples-on-Copying-and-Moving
      COMMAND copy_move)

