#include <iostream>
#include <string>
#include <vector>

namespace Test1
{
    //           ------ Will accept, lvalues, const lvalues or const rvalue references
    //           |      (const lvalue/rvalue reference)
    //           v
    void Print1(const std::string& s)
    {
        std::cout << s << std::endl;
    }
    void Test1()
    {
        std::string s1 { "lvalues are accepted" };
        Print1(s1); // binding string as const std::string --> Works
                    // Terminology: By calling Print1, we are trying to bind a const lvalue reference of type const std::string(the function part) to 
                    // the lvalue of type std::string (in this case, s1).
        
        const std::string s2 { "const lvalues are accepted" };
        Print1(s2); // binding const string as const std::string, CV is preserved --> Works
                    // Terminology: By calling Print1, we are trying to bind a const lvalue reference of type const std::string (the function part) to 
                    // the lvalue of type const std::string (in this case, s2).
        
        Print1(std::string{"const rvalues are accepted"} ); // binding as const rvalues --> Works
                                                            // Terminology: By calling Print1, we are trying to bind a const rvalue reference (the function part) to 
                                                            // the rvalue of type std::string
    }
}

