#include <iostream>
#include <string>


namespace T1
{
  void Foo() { std::cout << "Printing something random\n"; }
  void Doo(const int a) { std::cout << "Printing int argument(" << a << ")\n"; }
  int Goo(const std::string&& s) { std::cout << s << "\n"; return 0; }

  using TPrintRandom = void(*)();
  using TPrintInt = void(*)(const int);
  using TPrintString = int(*)(const std::string&&);

  void Test()
  {
    std::cout << "####################################### Test-1: Demonstrate aliasing global function\n";
    TPrintRandom pr = &Foo;
    pr();
    std::cout << std::endl;

    TPrintInt pi = &Doo;
    pi(437);
    std::cout << std::endl;

    TPrintString ps = &Goo;
    auto retVal = ps("Printing a string");
    std::cout << "Return value after execution of TPrintStrin=" << retVal << "\n";
  }
}

int main()
{
  T1::Test();
  return 0;
}



