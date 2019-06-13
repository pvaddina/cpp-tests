project(Rvalue-References-Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp test_legacy.h test3.h test4.h test5.h test6.h test7.h)

add_executable(rrefs ${SOURCES})
