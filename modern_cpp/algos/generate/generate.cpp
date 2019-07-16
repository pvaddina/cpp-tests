#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace T1
{
  auto global_gen = []() {
    auto initStart = 0;
    return [&]() mutable { 
      std::string start = "Zero";
      if      (initStart == 1) { start = "One"; }
      else if (initStart == 2) { start = "Two"; }
      else if (initStart == 3) { start = "Three"; }
      ++initStart;
      return start;
    };
  };

  
  class Foo
  {
    public:
      Foo(int sz, std::function<std::string()>& generator)
        : mNames(sz)
      {
        std::generate(mNames.begin(), mNames.end(), generator());
      }
    private:
      std::vector<std::string> mNames;
  };

  void Test1()
  {
    std::vector<std::string> numberStrings(4);
    std::generate(numberStrings.begin(), numberStrings.end(), global_gen());
    for (auto& st: numberStrings)
      std::cout << st << std::endl;
  }
}

int main()
{
  T1::Test();
  
  return 0;
}
