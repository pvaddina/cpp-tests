#include "test_legacy.h"
#include "test_rvalues.h"
#include "test4.h"
#include "test5.h"
#include "test6.h"
#include "test7.h"
#include "test8.h"
#include "test9.h"
#include "test_perfect_forwarding.h"


int main()
{
    Test1::RunTests();
    RValueTest::Test3();
    Test4::OverloadTests();
    Test5::Test5();
    Test6::Test6();
    Test7::Test7();
    Test8::Test();
    Test9::Test();
    Test10::Test();

    return 0;
}

