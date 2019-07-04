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
      Foo(StrWrapper& inS)
        : name(inS.s), id(437) {}

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

  template <typename C, typename ARG1>
  C* CreateFoo(ARG1& arg1)
  {
    return new Foo(arg1);
  }

#if 0
  template <typename... Args>
  C* CreateFooNew(Args&&... args)
  {
    return new Foo(std::forward<Args>(args)...);
  }
#endif

  void TestProblem()
  {
    StrWrapper s { "FooObject" };
    int lclId = 2;
    
    std::unique_ptr<Foo> f1 { CreateFoo<Foo>(s, lclId) };
    f1->Print();

    std::unique_ptr<Foo> f2 { CreateFoo<Foo>(StrWrapper("Rvalue string"), 437) };
    f2->Print();

    std::unique_ptr<Foo> f3 { CreateFoo<Foo>(s) };
    f3->Print();

    // Does not work !! Cannot pass an rvalue
    // std::unique_ptr<Foo> f4 { CreateFoo<Foo>(StrWrapper("Rvalue string")) };
  }


#if 0
  void TestPF_Solution()
  {
    StrWrapper s { "FooObject" };
    int lclId = 2;
    
    std::unique_ptr<Foo> f1 { CreateFooNew<Foo>(s, lclId) };
    f1->Print();

    std::unique_ptr<Foo> f2 { CreateFooNew<Foo>(StrWrapper("Rvalue string"), 437) };
    f2->Print();

    std::unique_ptr<Foo> f3 { CreateFooNew<Foo>(s) };
    f3->Print();

    // Does not work !! Cannot pass an rvalue
    std::unique_ptr<Foo> f4 { CreateFooNew<Foo>(StrWrapper("Rvalue string")) };
  }
#endif

  void Test()
  {
    TestProblem();
    //TestPF_Solution();
  }
}

