#include "test_legacy.h"
#include "test3.h"
#include "test4.h"
#include "test5.h"
#include "test6.h"
#include "test7.h"
#include "test8.h"
#include "test9.h"


int main()
{
    Test1::RunTests();
    Test3::Test3();
    Test4::OverloadTests();
    Test5::Test5();
    Test6::Test6();
    Test7::Test7();
    Test8::Test();
    Test9::Test();

    return 0;
}

