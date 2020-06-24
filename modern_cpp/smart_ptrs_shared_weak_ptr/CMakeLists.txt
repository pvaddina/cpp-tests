project(Smart-Pointers-Tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(shared main.cpp sp.h)

add_test(NAME SharedPtrTests
      COMMAND shared)

