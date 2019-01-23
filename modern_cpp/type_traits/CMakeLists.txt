project(Type-traits-tests)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp is_same.h)

add_executable(traits ${SOURCES})
