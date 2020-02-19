project(Variant-Demo)

set(CMAKE_CXX_STANDARD 17)

add_executable(variant var.cpp)

add_test(NAME All-about-Variant
      COMMAND variant)
