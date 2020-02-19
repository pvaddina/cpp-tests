project(Smart-Pointers-Tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(smart main.cpp)

add_test(NAME SmartPtrTests
      COMMAND smart)

