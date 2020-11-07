project(All-about-Tuple)

set(CMAKE_CXX_STANDARD 17)

add_executable(all_about_tuple main.cpp test1.h test2.h)

add_test(NAME All-about-Tuple
      COMMAND tupletest)
