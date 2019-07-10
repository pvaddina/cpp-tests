#include <memory>
#include <string>
#include <iostream>
#include <tuple>
#include <utility>

namespace Test9
{
  void Foo(std::string&& s)
  {
    std::string value = std::move(s);
    std::cout << "value in Foo=" << value << std::endl;
    std::cout << "s in Foo, after move=" << s << std::endl;
  }

  void Boo(std::string&& s)
  {
    //Foo(s); // cannot bind rvalue reference of type 'std::__cxx11::string&&' {aka 'std::__cxx11::basic_string<char>&&'} to lvalue of type 'std::__cxx11::string' {aka 'std::__cxx11::basic_string<char>'}

    Foo(std::forward<std::string>(s));
    std::cout << "s in Boo, WITHOUT a move=" << s << std::endl;
  }

  void Coo(std::string&& s)
  {    
    Foo(std::move(s));
    std::cout << "s in Coo, after move operation=" << s << std::endl;
  }

  template <typename T>
  void Goo(T&& s)
  {
    std::string value = std::move(s);
    std::cout << "value in Goo=" << value << std::endl;
    std::cout << "s in Goo, after move=" << s << std::endl;
  }

  template <typename T>
  void Hoo(T&& s)
  {
    T value = std::move(s);
    std::cout << "value in Hoo=" << value << std::endl;
    std::cout << "s in Hoo, after move=" << s << std::endl;
  }


  void Test_MoveImpact()
  {
    std::cout << "Test-1: Calling Foo(std::string&&)" << std::endl;
    Foo("Test string 1");

    std::cout << "\nTest-2: Calling Goo(T&&)" << std::endl;
    Goo("Test string 1");

    std::cout << "\nTest-3: Calling Hoo(T&&)" << std::endl;
    Hoo("Test string 1");

    std::cout << "\nTest-4: Calling Boo(std::string&&)" << std::endl;
    Boo("Test string 1");

    std::cout << "\nTest-5: Calling Coo(std::string&&)" << std::endl;
    Coo("Test string 1");
  }
}

