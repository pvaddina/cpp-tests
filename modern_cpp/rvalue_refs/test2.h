#include <iostream>
#include <string>
#include <vector>

namespace Test2
{
    //           ------ Will accept, lvalue references only
    //           |      (lvalue reference)
    //           v
    void Print1(std::string& s)
    {
        std::cout << s << std::endl;
    }
    void Test2()
    {
        std::string s1 { "lvalues are accepted" };
        Print1(s1); // binding string as const std::string --> Works
                    // Terminology: By calling Print1, we are trying to bind a non-const lvalue reference (the function part) to 
                    // the lvalue of type std::string (in this case, s1).
        
        //const std::string s2 { "const lvalues are accepted" };
        //Print1(s2); // --> Binding a const std::string to std::string& --> FAILS
                      // Terminology: By calling Print1, we are trying to bind a non-const lvalue reference (the function part) to 
                      // the lvalue of type const std::string (in this case, s2).
        
        //Print1(std::string{"const rvalues are accepted"} ); // --> Binding rvalues to non const lvalue type 
                                                              // Terminology: By calling Print1, we are trying to bind a non-const lvalue reference (the function part) to 
                                                              // the rvalue of type std::string (in this case, s1).
    }
}


