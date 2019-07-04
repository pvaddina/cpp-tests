#include "test1.h"
#include "test2.h"
#include "test3.h"
#include "test4.h"
#include "test5.h"
#include "test6.h"
#include "test7.h"
#include "test8.h"
#include "test9.h"
#include "test_perfect_forwarding.h"


int main()
{
#if 0
    Test1::Test1();
    Test2::Test2();
    Test3::Test3();
    Test4::Test4();
    Test5::Test5();
    Test6::Test6();
    Test7::Test7();
    Test8::Test();
    Test9::Test();
#endif
    Test10::TestPerfectForwarding();

    return 0;
}

