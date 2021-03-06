#include <iostream>
#include <string>
#include <sstream>

namespace A
{
  class Foo
  {
    public:
      Foo(const std::string _s, const int _i) : s(_s), id(_i) { std::cout << "In constructor\n"; }
      Foo(const Foo& rhs) { s=rhs.s; std::cout << "In copy constructor\n"; }
      void operator=(const Foo& rhs) { s = rhs.s; std::cout << "In assignment operator\n"; }
      void Print() const
      {
        std::stringstream pstr;
        pstr << "s=" << s << ", id=" << id << "\n";
        std::cout << pstr.str();
      }

    private:
      std::string s;
    public:
      int id;
  };

  class FooWrapper
  {
    public:
      FooWrapper(const Foo& ip) : obj(ip) {}
      Foo GetFoo1() const { return obj; }
      Foo& GetFoo2() { return obj; }
      const Foo& GetFoo3() { return obj; }
      const Foo& GetFoo4() const { return obj; }
      // error: binding reference of type 'Foo&' to 'const Foo' discards qualifiers
      // Foo& GetFoo2() const { return obj; }

    private:
      Foo obj;
  };

  void Test1()
  {
    Foo f("Some test string", 437);
    FooWrapper obj(f);
    std::cout << "Test1: Foo GetFoo1() const { return obj; }\n";
    Foo ret = obj.GetFoo1();
    ret.Print();
  }

  void Test2()
  {
    Foo f("Some test string", 437);
    FooWrapper obj(f);
    std::cout << "Test2: Foo& GetFoo2() const { return obj; }\n";
    Foo& ret = obj.GetFoo2();
  }

  void Test3()
  {
    Foo f("Some test string", 437);
    FooWrapper obj(f);
    std::cout << "Test3: const Foo& GetFoo3() { return obj; }\n";
    const Foo& ret = obj.GetFoo3();
  }

  void Test4()
  {
    Foo f("Some test string", 437);
    FooWrapper obj(f);
    std::cout << "Test4: const Foo& GetFoo4() const { return obj; }\n";
    const Foo& ret = obj.GetFoo4();
  }

  void do_const_obj_tests()
  {
    std::cout << "In do_const_obj_tests\n";
    Test1();
    Test2();
    Test3();
    Test4();
  }
}
