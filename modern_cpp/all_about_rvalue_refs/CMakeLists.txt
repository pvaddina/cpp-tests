project(Rvalue-References-Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp test3.h test4.h test5.h test6.h test7.h test_legacy.h test_perfect_forwarding.h)

add_executable(rrefs ${SOURCES})
