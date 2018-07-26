#include <iostream>
#include <string>


class Foo
{
  public:
    Foo(const int _p, const std::string& _s)
      : p(_p), v(_s) {}

    Foo(Foo const& rhs)
    {
      std::cout << "In Foo::Foo(Foo const&)" << std::endl;
      p = rhs.p;
      v = rhs.v;
    }

  private:
    int p;
    std::string v;
};


int do_gen_tests_2()
{
  Foo f(437, "This is an std::string");
}
