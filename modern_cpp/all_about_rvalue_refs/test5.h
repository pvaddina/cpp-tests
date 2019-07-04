#include <iostream>
#include <string>
#include <vector>

namespace Test5
{
  struct TMoveConstruction
  {
    int v = 437;
    double d = 22.3434;
    std::string str = "T1-String";
    TMoveConstruction(int&& _v, double&& _d, std::string&& _s) : v(_v), d(_d), str(_s) {}
  };

  struct Wrapper
  {
    Wrapper(const TMoveConstruction& t) : localT(t) {}
    const TMoveConstruction localT;
  };

  void Test5()
  {
    TMoveConstruction t1{ std::move(5), std::move(23.43534), std::move(std::string("Some user string")) }; // With explicit move cast
    std::cout << t1.v << " - " << t1.d << " - " << t1.str << std::endl;

    TMoveConstruction t2{ 6, 3425.546, std::string("Another user string") };    // You dont even need an explicit move
    std::cout << t2.v << " - " << t2.d << " - " << t2.str << std::endl;

    std::string s{ "An l-value string" };
    TMoveConstruction t3{ std::move(5), std::move(23.43534), std::move(s) }; // Pass an lValue
    std::cout << t3.v << " - " << t3.d << " - " << t3.str << std::endl;
    std::cout << s << std::endl;

#if 0
    const std::string constStr{ "A const l-value string" };
    TMoveConstruction t4{ std::move(5), std::move(23.43534), constStr }; // Cannot bind rvalue reference (constructor of TMoveConstruction) to an lvalue of 'const string'
    TMoveConstruction t4{ std::move(5), std::move(23.43534), std::move(constStr) }; // Forcing the bind to an rvalue reference (constructor of TMoveConstruction) discards qualifiers
#endif
  }
}

