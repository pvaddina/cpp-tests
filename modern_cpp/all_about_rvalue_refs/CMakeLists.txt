project(Rvalue-References-Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp test_copyeffects.h test_doublepassing.h test_legacy.h test_moveconstruction.h test_overloads.h test_perfect_forwarding test_reference_collapsing.h test_tuples_with_rvalues.h)

add_executable(rrefs ${SOURCES})
