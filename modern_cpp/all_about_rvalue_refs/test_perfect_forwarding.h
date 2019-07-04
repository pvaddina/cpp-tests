#include <memory>
#include <string>
#include <iostream>

namespace Test10
{
  struct StrWrapper
  {
    StrWrapper(std::string&& _s) : s{_s} {}
    StrWrapper(const StrWrapper& _inStrWrapper) : s {_inStrWrapper.s } { std::cout << "In Copy Constructor" << std::endl; }
    std::string s;
  };

  class Foo
  {
    public:
      Foo(const StrWrapper& inS, const int _id)
        : name(inS.s), id(_id) {}

    void Print()
    {
      std::cout << "Name:" << name << ", id=" << id << std::endl;
    }
      
    private:
      std::string name;
      int id;
  };


  template <typename C, typename ARG1, typename ARG2>
  C* CreateFoo(const ARG1& arg1, const ARG2& arg2)
  {
    return new Foo(arg1, arg2);
  }

  void TestPerfectForwarding()
  {
    StrWrapper s { "FooObject" };
    int lclId = 2;
    
    std::unique_ptr<Foo> f1 { CreateFoo<Foo>(s, lclId) };
    f1->Print();

    std::unique_ptr<Foo> f2 { CreateFoo<Foo>(s, 437) };
    f2->Print();
  }
}

