#include <iostream>
#include <sstream>
#include <string>
#include <functional>


namespace T1
{
  using FN = std::function<std::string(const int, const std::string)>;

  struct Foo
  {
    std::string MakeStr(const int i, const std::string s)
    {
      std::stringstream ss;
      ss << "Foo::MakeStr(): i=" << i << ", s=" << s << "\n";
      return ss.str();
    }
  };

  std::string Coo(const int i, const std::string s)
  {
    std::stringstream ss;
    ss << "Coo: i=" << i << ", s=" << s << "\n";
    return ss.str();
  }

  void LooseFunctions()
  {
    FN f = Coo;
    std::cout << f(1, "Number-1");

    FN f1 {Coo};
    std::cout << f1(1, "Number-1");

  }

  void LambdaTests()
  {
    FN fLambda {[](const int i, const std::string s)->std::string {
      std::stringstream ss;
      ss << "Test::lambda: i=" << i << ", s=" << s << "\n";
      return ss.str();
    }};
    std::cout << fLambda(2, "Number-2");
  }

  void MemberFns()
  {
    Foo fObj;

    using std::placeholders::_1;
    using std::placeholders::_2;
    FN f = std::bind(&Foo::MakeStr, fObj, _1, _2);
    std::cout << f(2, "Number-2");

    FN f1 = [&](const int i, const std::string s)->std::string {
      return fObj.MakeStr(i,s);
    };
    std::cout << f1(2, "Number-2");
  }
}

int main()
{
  T1::LooseFunctions();
  T1::LambdaTests();
  T1::MemberFns();
  return 0;
}



