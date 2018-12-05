#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>

// A simple test to show the use of constexpr members within a class
namespace T1
{
  struct T1
  {
    // constexpr int someV = 437; // --> Error: the value is not static. Non-static data member 'someV' declared 'constexpr'

    // Note that this usage is no better than the traditional 'static const', or is there any ???
    static constexpr int v = 437;
    static constexpr double d = 22.3434;
    void Print() { std::cout << v << " " << d << std::endl; }
  };

  void Test()
  {
    std::cout << "In T1::Test" << std::endl;
    T1 t;
    t.Print();
  }
}

namespace T2
{
  void Alter(int& i) { i = 437; }

  void Test()
  {
    std::cout << "In T2::Test" << std::endl;
    auto val = 0;
    auto p = &val;
    Alter(*p);
    std::cout << "Val = " << val << std::endl;
  }
}


int main()
{
  T1::Test();
  std::cout << "\n";
  T2::Test();
  return 0;
}
