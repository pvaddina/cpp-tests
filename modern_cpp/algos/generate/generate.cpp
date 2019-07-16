#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

namespace T1
{
  class Foo
  {
    public:
      Foo(int sz, std::function<std::string()>&& generator)
        : mNames(sz)
      {
        std::generate(mNames.begin(), mNames.end(), generator);
      }
    private:
      std::vector<std::string> mNames;
  };

  void Test()
  {
    auto initStart = 0;

    auto value_gen = [initStart]() mutable {
      std::string value = "Zero";
      if      (initStart == 1) { value = "One"; }
      else if (initStart == 2) { value = "Two"; }
      else if (initStart == 3) { value = "Three"; }
      ++initStart;
      return value;
    };

    std::vector<std::string> numberStrings(4);
    std::generate(numberStrings.begin(), numberStrings.end(), value_gen);
    for (auto& st: numberStrings)
      std::cout << st << std::endl;
  }
}

int main()
{
  T1::Test();
  
  return 0;
}
