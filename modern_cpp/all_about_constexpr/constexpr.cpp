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

#if 0
namespace T3
{
  struct GuidConst
  {
    int v1;
    int v2;
    int v3;
    struct LastDigit
    {
      constexpr bool operator==(const LastDigit& ld) { return l1==ld.l1 && l2==ld.l2; }
      int l1;
      int l2;
    };
    LastDigit v4;
    constexpr bool operator==(const GuidConst& gid) { return v1==gid.v1 && v2==gid.v2 && v3==gid.v3 && v4==gid.v4; }
  };

  constexpr GuidConst One = {11, 111, 1111, {11111, 111111}};
  constexpr GuidConst Two = {22, 222, 2222, {22222, 222222}};
  constexpr GuidConst Three = {33, 333, 3333, {33333, 333333}};

  struct Foo
  {
    constexpr Foo(GuidConst& _v) : v{_v} {}

    void Print()
    {
      if constexpr (v == One)
      {
        std::cout << "This is One" << std::endl;
      }
      else if constexpr (v == Two)
      {
        std::cout << "This is Two" << std::endl;
      }
      if constexpr (v == Three)
      {
        std::cout << "This is Three" << std::endl;
      }
    }

    private:
      GuidConst v;
  };

  void Test()
  {
    constexpr Foo<One> one;
    constexpr Foo<Two> two;
    constexpr Foo<Three> three;
  }
}
#endif


int main()
{
  T1::Test();
  std::cout << "\n";
  T2::Test();
  std::cout << "\n";
  //T3::Test();
  return 0;
}
