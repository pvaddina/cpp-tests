project(ComplexConditions)

set(CMAKE_CXX_STANDARD 11)

add_executable(complex_conditions main.cpp)

add_test(NAME complex_conditions_tests
         COMMAND complex_conditions)
