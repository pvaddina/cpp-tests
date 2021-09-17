project(List_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(list test.cpp)

add_test(NAME list_test
      COMMAND list)
