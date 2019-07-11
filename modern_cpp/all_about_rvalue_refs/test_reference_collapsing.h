#pragma once

#include <vector>
#include <string>
#include <iostream>

namespace Test11
{
  template <typename T>
  struct Foo
  {
    public:
      template <typename V>
      void Print(V&& v)
      {
        std::cout << "template<typename S>void Print(S&& v): v=" << v << std::endl;
        //v = "Replaced string";
      }

      void PrintTypeT(T&& v)
      {
        std::cout << "void PrintTypeT(T&& v): v=" << v << std::endl;
      }
  };

  void TestNormalFunctionCall()
  {
    Foo<std::string> f1;
    std::string s {"Some lvalue string. Template argument \'V\' is deduced to std::string&. And Due to reference collapsing, && & results in &." };
    
    // OK to call with an lvalue (Reference collapsing: V deduced as std::string&. && & collapses to &)
    f1.Print(s);

    // OK to call with an rvalue
    f1.Print("Random rvalue string. Template argument \'V\' is deduced to std::string&&. And Due to reference collapsing, && && results in &&" );

    //
    // Note that for the function, "PrintTypeT", no template type deduction rules apply, because it is not a template function. 
    // T in this case is the class template argument and not a function template argument.
    // 
    // OK to call 'PrintTypeT' with an rvalue. T is std::string. 
    f1.PrintTypeT("Passing rvalues is OK");

    // Cannot pass lvalues. The function, PrintTypeT only accepts rvalues of type 'T' (std::string in this case)
    // f1.PrintTypeT(s);
  }


  void Test_ReferenceCollapsing()
  {
    std::cout << "######################################## Test_ReferenceCollapsing\n";
    TestNormalFunctionCall();
  }
}


