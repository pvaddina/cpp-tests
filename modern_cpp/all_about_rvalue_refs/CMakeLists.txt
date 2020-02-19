project(Rvalue-References-Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp test_copyeffects.h test_doublepassing.h test_legacy.h test_moveconstruction.h test_overloads.h test_perfect_forwarding test_impact_of_move.h test_tuples_with_rvalues.h test_reference_collapsing.h)

add_executable(rrefs ${SOURCES})

add_test(NAME All-about-RValue-References
      COMMAND rrefs)
