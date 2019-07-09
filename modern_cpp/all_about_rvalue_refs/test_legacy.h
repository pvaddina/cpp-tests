#include <iostream>
#include <string>
#include <vector>

namespace Test1
{
    //                ------ Will accept, lvalues, const lvalues or const rvalue references
    //               |      (const lvalue/rvalue reference)
    //               v
    void PrintConst(const std::string& s)
    {
        std::cout << s << std::endl;
    }

    //                   ------ Will accept, lvalue references only
    //                   |      (lvalue reference)
    //                   v
    void PrintNonConst(std::string& s)
    {
        std::cout << s << std::endl;
    }


    void ConstTests()
    {
        std::string s1 { "lvalues are accepted" };
        PrintConst(s1); // binding string as const std::string --> Works
                    // Terminology: By calling PrintConst, we are trying to bind a const lvalue reference of type const std::string(the function part) to 
                    // the lvalue of type std::string (in this case, s1).
        
        const std::string s2 { "const lvalues are accepted" };
        PrintConst(s2); // binding const string as const std::string, CV is preserved --> Works
                    // Terminology: By calling PrintConst, we are trying to bind a const lvalue reference of type const std::string (the function part) to 
                    // the lvalue of type const std::string (in this case, s2).
        
        PrintConst(std::string{"const rvalues are accepted"} ); // binding as const rvalues --> Works
                                                            // Terminology: By calling PrintConst, we are trying to bind a const rvalue reference (the function part) to 
                                                            // the rvalue of type std::string
    }

    void NonConstTests()
    {
        std::string s1 { "lvalues are accepted" };
        PrintNonConst(s1); // binding string as const std::string --> Works
                    // Terminology: By calling PrintNonConst, we are trying to bind a non-const lvalue reference (the function part) to 
                    // the lvalue of type std::string (in this case, s1).
        
        //const std::string s2 { "const lvalues are accepted" };
        //PrintNonConst(s2); // --> Binding a const std::string to std::string& --> FAILS
                      // Terminology: By calling PrintNonConst, we are trying to bind a non-const lvalue reference (the function part) to 
                      // the lvalue of type const std::string (in this case, s2).
        
        //PrintNonConst(std::string{"const rvalues are accepted"} ); // --> Binding rvalues to non const lvalue type 
                                                              // Terminology: By calling PrintNonConst, we are trying to bind a non-const lvalue reference (the function part) to 
                                                              // the rvalue of type std::string (in this case, s1).
    }


    void RunTests()
    {
      std::cout << "######################################## Testing legacy cases ...." << std::endl;
      ConstTests();
      NonConstTests();
    }
}

