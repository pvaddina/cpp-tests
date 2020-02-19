project(All-About-Lambdas)

set(CMAKE_CXX_STANDARD 17)

add_executable(lambda_test lamda.cpp)

add_test(NAME Know-all-about-Lambdas
      COMMAND lambda_test)
