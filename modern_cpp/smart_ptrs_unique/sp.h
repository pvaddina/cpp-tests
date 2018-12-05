#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <array>


struct StFoo
{
  StFoo() = default;
  StFoo(const StFoo&) = delete;
  StFoo(std::string&& _s) : s(_s) {}
  StFoo(int i, std::string&& _s) : p(i), s(_s) {}
  int p { 437 };
  std::string s { "Some test string" };
  void Print() { std::cout << "p = " << p << ", s=" << s << std::endl; }
};

namespace SP1
{
}


int test_shared_ptr()
{
  return 0;
}
