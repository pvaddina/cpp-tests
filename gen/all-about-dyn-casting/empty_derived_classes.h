#include <iostream>
#include <string>

namespace T1
{
  class Base { 
    public:
      virtual ~Base()=default;
  };
  class D1 : public Base { };
  class D2 : public Base { };
  class D3 : public Base { };

  template<typename T>
  void CastItToPtr(Base* b, std::string&& name)
  {
    const auto ptr = dynamic_cast<T*>(b);
    if(ptr)       { std::cout << name << " pointer detected" << std::endl; }
  }

  template<typename T>
  void CastItToRef(Base& b, std::string&& name)
  {
    const auto ptr = dynamic_cast<T*>(&b);
    if(ptr)       { std::cout << name << " reference detected" << std::endl; }
  }

  void CastPtr(Base* b)
  {
    CastItToPtr<D1>(b, "D1");
    CastItToPtr<D2>(b, "D2");
    CastItToPtr<D3>(b, "D3");
  }

  void CastRef(Base& b)
  {
    CastItToRef<D1>(b, "D1");
    CastItToRef<D2>(b, "D2");
    CastItToRef<D3>(b, "D3");
  }

  void Test()
  {
    std::cout << "############################## In T1::Test\n";
    D1 d1;
    CastPtr(&d1);
    CastRef(d1);
    D3 d3;
    CastPtr(&d3);
    CastRef(d3);
    D2 d2;
    CastPtr(&d2);
    CastRef(d2);
  }
}

namespace T2
{
  class Base { 
    public:
      virtual ~Base()=default;
  };
  class D1 : public Base { };
  class D2 : public Base { };
  class D3 : public Base { };

  void D1Foo(const D1& d) { std::cout << "Processing D1" << std::endl; }
  void D2Foo(const D2& d) { std::cout << "Processing D2" << std::endl; }
  void D3Foo(const D3& d) { std::cout << "Processing D3" << std::endl; }

  void CastRef(Base& b)
  {
    const auto pD1 = dynamic_cast<D1*>(&b);
    if (pD1)
      D1Foo(*pD1);
    const auto pD2 = dynamic_cast<D2*>(&b);
    if (pD2)
      D2Foo(*pD2);
    const auto pD3 = dynamic_cast<D3*>(&b);
    if (pD3)
      D3Foo(*pD3);
  }

  void Test()
  {
    std::cout << "\n############################## In T2::Test\n";
    D1 d1;
    CastRef(d1);
    D3 d3;
    CastRef(d3);
    D2 d2;
    CastRef(d2);
  }
}
