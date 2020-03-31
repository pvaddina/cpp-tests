#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace T1
{
  using FN1 = std::vector<int>(const int);
  using FN2 = std::string(const int);

  template<typename FN>
  auto Process(const FN& f) -> decltype(f(0)) // Need the declaration to determine the declaration
  {
      return f(10);
  }

  std::vector<int> RetVec(const int i)
  {
      std::vector<int> retVec;
      for (int it=0; it<i; ++it)
          retVec.push_back(it);
      return retVec;
  }

  std::string RetStr(const int i)
  {
      std::string str;
      for (int it=0; it<i; ++it)
          str += "* ";
      return str;
  }

  void NoRetStr(const int i)
  {
      for (int it=0; it<i; ++it)
          std::cout << "-- ";
  }

  void Test()
  {
      auto vec = Process(&RetVec);
      for (auto& i: vec)
          std::cout << i << " ";
      std::cout << std::endl;
          
      auto s = Process(&RetStr);
      std::cout << s << std::endl;
      
      Process(&NoRetStr);
  }
}

int main()
{
  T1::Test();
  return 0;
}


