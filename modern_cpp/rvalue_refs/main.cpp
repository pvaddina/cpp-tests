#include "test1.h"
#include "test2.h"
#include "test3.h"
#include "test4.h"

int main()
{
    #if 0
    Test1::Test1();
    Test2::Test2();
    Test3::Test3();
    #endif
    Test4::Test4();
    
    return 0;
}

