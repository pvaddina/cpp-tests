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

  struct FooAdvanced
  {
    FooAdvanced(const int v) : mVal(v) { std::cout << "In FooAdvanced constructor\n"; }
    FooAdvanced(const FooAdvanced& f) : mVal(f.mVal) { std::cout << "In FooAdvanced copy constructor\n"; }

    std::string MakeStr(const int i, const std::string s)
    {
      std::stringstream ss;
      ss << "Foo::MakeStrWithInternal(): i=" << i << ", s=" << s << ", mVal=" << mVal << "\n";
      return ss.str();
    }

    private:
      int mVal = 100;
  };


  std::string Coo(const int i, const std::string s)
  {
    std::stringstream ss;
    ss << "Coo: i=" << i << ", s=" << s << "\n";
    return ss.str();
  }

  void LooseFunctions()
  {
    std::cout << "###################### In LooseFunctions()\n";
    FN f = Coo;
    std::cout << f(1, "Number-1");

    FN f1 {Coo};
    std::cout << f1(1, "Number-1");
  }

  void LambdaTests()
  {
    std::cout << "\n###################### In LambdaTests()\n";
    FN fLambda {[](const int i, const std::string s)->std::string {
      std::stringstream ss;
      ss << "Test::lambda: i=" << i << ", s=" << s << "\n";
      return ss.str();
    }};
    std::cout << fLambda(2, "Number-2");
  }

  void MemberFns()
  {
    std::cout << "\n###################### In MemberFns()\n";
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

  void DeletedObjects()
  {
    std::cout << "\n###################### In DeletedObjects()\n";
    FooAdvanced* fObj { new FooAdvanced(200) };

    using std::placeholders::_1;
    using std::placeholders::_2;
    FN f = std::bind(&FooAdvanced::MakeStr, fObj, _1, _2);
    std::cout << "Call using pointer to the FooAdvanced object: " << f(2, "Number-2");

    FN f1 = std::bind(&FooAdvanced::MakeStr, std::ref(*fObj), _1, _2);
    std::cout << "Call using FooAdvanced reference object: " << f1(2, "Number-2");

    FN f2 = std::bind(&FooAdvanced::MakeStr, *fObj, _1, _2);
    std::cout << "Call using FooAdvanced copy object: " << f2(2, "Number-2");

    delete fObj;
    std::cout << "Call using pointer to the FooAdvanced object after delete: " << f(2, "Number-2");
    std::cout << "Call using FooAdvanced reference object after delete: " << f1(2, "Number-2");
    std::cout << "Call using FooAdvanced copy object after delete: " << f2(2, "Number-2");

#if 0
    FN f1 = [&](const int i, const std::string s)->std::string {
      return fObj.MakeStr(i,s);
    };
    std::cout << f1(2, "Number-2");
#endif
  }
}

int main()
{
  T1::LooseFunctions();
  T1::LambdaTests();
  T1::MemberFns();
  T1::DeletedObjects();
  return 0;
}



