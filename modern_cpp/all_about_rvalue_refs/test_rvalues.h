#include <iostream>
#include <string>
#include <vector>

namespace RValueTest
{
    //           ------ Will accept, rvalue references only
    //           |      (rvalue reference)
    //           v
    void Print1(std::string&& s)
    {
        std::cout << s << std::endl;
    }
    void Test3()
    {
        std::cout << "######################################## Testing rvalue function arguments ...." << std::endl;
        //std::string s1 { "lvalues are accepted" };
        //Print1(s1); // error: cannot bind rvalue reference of type 'std::__cxx11::string&&' {aka 'std::__cxx11::basic_string<char>&&'} to lvalue of type 'const string'
                      // Terminology: By calling Print1, we are trying to bind a rvalue reference of type std::string (the function part) to 
                      // the lvalue of type std::string (in this case, s1).
        
        //const std::string s2 { "const lvalues are accepted" };
        //Print1(s2); // error: cannot bind rvalue reference of type 'std::__cxx11::string&&' {aka 'std::__cxx11::basic_string<char>&&'} to lvalue of type 'const string'
        
        Print1(std::string{"const rvalues are accepted"} ); // Binding rvalues to non const lvalue type 
    }
}
