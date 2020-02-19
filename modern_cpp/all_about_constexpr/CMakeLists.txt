project(All-about-Constexpr)

set(CMAKE_CXX_STANDARD 17)

add_executable(constexpr constexpr.cpp)

add_test(NAME Know-all-about-Constexpr
      COMMAND constexpr)

