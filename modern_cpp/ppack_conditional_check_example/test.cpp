#include <iostream>
#include <functional>
#include "sfinae.h"
#include "if_constexpr.h"

template <typename... Ts>
void TestBoth(Ts... ts)
{
  int i = 0;
  SFINAE::SetValue(i, std::forward<Ts>(ts)...);
  std::cout << "Value using SFINAE::SetValue:" << i << std::endl;

  int j = 0;
  ConstExpression::SetValue(j, std::forward<Ts>(ts)...);
  std::cout << "Value using ConstExpression::SetValue:" << j << std::endl;
}

void RunTests1()
{
  TestBoth([]() { return false; }, 444
         , []() { return false; }, 999
         , []() { return true; }, []() { return 222; });

  TestBoth([]() { return false; }, 444
         , []() { return true; }, 999
         , []() { return true; }, []() { return 222; });

  TestBoth([]() { return false; }, 444
         , []() { return false; }, 999
         , []() { return false; }, []() { return 222; });
}

int main()
{
  RunTests1();
}

