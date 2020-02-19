project(All-About-FoldExpressions)

set(CMAKE_CXX_STANDARD 17)

add_executable(fold_exp_test fold.cpp)

add_test(NAME All-about-Fold-expressions
      COMMAND fold_exp_test)


