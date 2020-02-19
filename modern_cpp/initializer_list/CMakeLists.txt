project(Initializer-List-Demo)

set(CMAKE_CXX_STANDARD 11)

add_executable(init_list init_list.cpp)

add_test(NAME Initializer-List-Demo
      COMMAND init_list)
