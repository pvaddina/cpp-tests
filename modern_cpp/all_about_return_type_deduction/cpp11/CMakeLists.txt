project(All-About-Return-type-deduction-in-CPP11)

set(CMAKE_CXX_STANDARD 11)

add_executable(ret11 cpp11.cpp)
target_compile_options(ret11 PUBLIC -DCPP_11)

add_test(NAME Know-about-return-type-deduction-cpp11
      COMMAND ret11)
