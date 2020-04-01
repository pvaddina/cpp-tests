project(All-About-Return-type-deduction-in-CPP14_and_CPP17)

set(CMAKE_CXX_STANDARD 14)

add_executable(ret14_17 cpp14_17.cpp)
target_compile_options(ret14_17 PUBLIC -DCPP_14_17)

add_test(NAME Know-about-return-type-deduction-cpp14_and_cpp17
      COMMAND ret14_17)
