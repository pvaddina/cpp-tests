project(PPack-Conditional-Statements-Recipe)

set(CMAKE_CXX_STANDARD 17)

add_executable(ppack_cond sfinae.h if_constexpr.h test.cpp)
