#include "test_copyeffects.h"
#include "test_doublepassing.h"
#include "test_legacy.h"
#include "test_moveconstruction.h"
#include "test_overloads.h"
#include "test_perfect_forwarding.h"
#include "test_reference_collapsing.h"
#include "test_tuples_with_rvalues.h"


int main()
{
    Test1::Test_Legacy();
    Test4::OverloadTests();
    Test5::Test_MoveConstruction();
    Test6::Test_CopyEffects();
    Test7::Test_DoublePassing();
    Test8::Test_TupleWithRValues();
    Test9::Test_ReferenceCollapsing();
    Test10::Test_PerfectForwarding();

    return 0;
}

