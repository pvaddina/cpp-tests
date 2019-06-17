project(Type-traits-tests)

set(CMAKE_CXX_STANDARD 17)

set(COMMON_TRAITS_SOURCES main.cpp is_same.h)

add_executable(common_traits      ${COMMON_TRAITS_SOURCES})
add_executable(enable_if_sfinae   eif.cpp)


