#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <array>
#include <functional>

template <typename DST, typename COND, typename GETTER>
void SetVal(DST& dest, DST&& def, COND&& cond, GETTER&& getter)
{
  if (cond()) dest = getter();
  else dest = def;
}

auto Setter = [](auto& dest, auto&& def, auto&& cond, auto&& getter)
{
  if (cond()) dest = getter();
  else dest = def;
};


void TemplatesVsGenLambda()
{
  auto trueChecker = []()  { return true;  };
  auto falseChecker = []() { return false; };

  auto val437 = []() { return 437; };
  auto val999 = []() { return 999; };

  int tempResult;
  SetVal(tempResult, 0, trueChecker, val437);
  std::cout << tempResult << std::endl;

  SetVal(tempResult, 0, falseChecker, val999);
  std::cout << tempResult << std::endl;

  int lambdaResult;
  Setter(lambdaResult, 0, trueChecker, val437);
  std::cout << lambdaResult << std::endl;

  Setter(lambdaResult, 0, falseChecker, val999);
  std::cout << lambdaResult << std::endl;
}




int main()
{
  TemplatesVsGenLambda();
  return 0;
}



