#include <iostream>
#include <string>
#include <vector>
#include <functional>

namespace T1
{
  using FN1 = std::vector<int>(const int);
  using FN2 = std::string(const int);

#ifdef CPP_11
  template<typename FN>
  auto Process(const FN& f) -> decltype(f(0)) // Need the declaration to determine the declaration
  {
      return f(10);
  }
#elif CPP_14_17
  template<typename FN>
  auto Process(const FN& f) // No need of any further declaration
  {
      return f(10);
  }
#endif

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

  struct Foo
  {
    Foo(std::string&& s) : name(std::move(s)) {}

    void VoidPrint(const int n)
    {
      for (int i=0; i<n; ++i)
        std::cout << "VoidPrint: " << name << std::endl;
    }

    int IntPrint(const int n)
    {
      for (int i=0; i<n; ++i)
        std::cout << "IntPrint: " << name << std::endl;
      return 0;
    }
    private:
      std::string name;
  };

  void Test()
  {
      auto vec = Process(&RetVec);
      for (auto& i: vec)
          std::cout << i << " ";
      std::cout << std::endl;
          
      auto s = Process(&RetStr);
      std::cout << s << std::endl;
      
      Process(&NoRetStr);
      
      Process([](const int i) -> void { std::cout << "\nIn a closure. Nothing returned\n"; });
      
      Foo fObj("Foo object");
      Process([&](const int i) -> void { fObj.VoidPrint(i); });

      Process([&](const int i) -> int { return fObj.IntPrint(i); });
  }
}

