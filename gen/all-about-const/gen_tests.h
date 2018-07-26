#include <iostream>

void test1(int * const p) // Note the pointer is constant, not the value that it points to. 
{
    // Attempt to change the value pointed by 'p'. This is fine as it is not declared as constant. 
    *p = 333;    
    
    // ERROR !! Attempt to change the pointer itself (p). It is also constant. Cannot be changed.
    //int localV = 999;  
    // p = &localV;
    std::cout << *p << std::endl;
}

// Note the 'const' specifier before and after the '*'. Before means the value pointed
// by p is constant and cannot be changed. And the value after the constant means that 
// 'p' itself cannot be changed
void test2(int const * const p) 
{
    // ERROR !! Attempt to change the value pointed by 'p'
    //*p = 333;
    
    // ERROR !! Attempt to change the pointer itself (p). It is also constant. Cannot be changed.
    //int localV = 999;  
    // p = &localV;
    std::cout << *p << std::endl;
}

// *p is declared constant. The value pointed by p cannot be changed. 
// The declaration, "const int* p" and "int const *p" are exactly the same
void test3(const int* p) 
{
    // ERROR !! Attempt to change the pointer itself (p). It is also constant. Cannot be changed.
    // *p = 999;
    std::cout << *p << std::endl;
}

// *p is declared constant. The value pointed by p cannot be changed. Same behavior as in test3. 
// The declaration, "const int* p" and "int const *p" are exactly the same
void test4(int const* p) 
{
    // ERROR !! Attempt to change the pointer itself (p). It is also constant. Cannot be changed.
    // *p = 999;
    std::cout << *p << std::endl;
}



int do_gen_tests()
{
    int v = 437;
    test1(&v);
    test2(&v);
    test3(&v);
    test4(&v);
}
