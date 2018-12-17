project(Rvalue-References-Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp test1.h test2.h test3.h test4.h test5.h test6.h)

add_executable(rrefs ${SOURCES})
