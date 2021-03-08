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
  void CastIt(Base* b, std::string&& name)
  {
    const auto ptr = dynamic_cast<T*>(b);
    if(ptr)       { std::cout << name << " pointer detected" << std::endl; }
  }

  void CastPtr(Base* b)
  {
    CastIt<D1>(b, "D1");
    CastIt<D2>(b, "D2");
    CastIt<D3>(b, "D3");
  }

  void EmptyDerivedClasses()
  {
    std::cout << "############################## In T1::Test\n";
    D1 d1;
    CastPtr(&d1);
    D3 d3;
    CastPtr(&d3);
    D2 d2;
    CastPtr(&d2);
  }
}
