#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace T1
{
  struct A { void PrintA() { std::cout << "Event A" << std::endl; } };
  struct B { void PrintB() { std::cout << "Event B" << std::endl; } };
  struct C { void PrintC() { std::cout << "Event C" << std::endl; } };
  struct D { void PrintD() { std::cout << "Event D" << std::endl; } };
  struct E { void PrintE() { std::cout << "Event E" << std::endl; } };

  struct RunBase
  {
    virtual void operator()() = 0;
    virtual ~RunBase() {}
  };


  template <typename T>
    struct Run : public RunBase
  {
    using FUNC = void (T::*)();
    Run(T& o, FUNC&& f) : mObj(o), mFunc(f) {}
    void operator()() override { (mObj.*mFunc)(); }

    T& mObj;
    FUNC mFunc;
  };

  void Test()
  {
    A a; 
    B b; 
    C c; 
    D d; 
    E e; 

    std::vector<std::unique_ptr<RunBase> > mFuncs;
    mFuncs.push_back(std::make_unique<Run<A> >(a, &A::PrintA));
    mFuncs.push_back(std::make_unique<Run<B> >(b, &B::PrintB));
    mFuncs.push_back(std::make_unique<Run<C> >(c, &C::PrintC));
    mFuncs.push_back(std::make_unique<Run<D> >(d, &D::PrintD));
    mFuncs.push_back(std::make_unique<Run<E> >(e, &E::PrintE));
    mFuncs.push_back(std::make_unique<Run<A> >(a, &A::PrintA));
    mFuncs.push_back(std::make_unique<Run<C> >(c, &C::PrintC));
    mFuncs.push_back(std::make_unique<Run<C> >(c, &C::PrintC));
    mFuncs.push_back(std::make_unique<Run<D> >(d, &D::PrintD));
    mFuncs.push_back(std::make_unique<Run<E> >(e, &E::PrintE));

    for (auto& i : mFuncs)
      (*i)();
  }

}

