project(Variable-Templates)

set(CMAKE_CXX_STANDARD 14)

add_executable(vartemplates main.cpp)

add_test(NAME VariableTemplates
      COMMAND vartemplates)

