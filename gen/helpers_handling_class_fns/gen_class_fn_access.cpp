#include <iostream>

struct C
{
  void printName(){ std::cout << "This is C" << std::endl; }
} c;

struct D
{
  void print(){ std::cout << "This is D" << std::endl; }
} d;

template <typename T>
struct FN_DEF { typedef void (T::*P_FN)(); };

template <typename T, typename FN_DEF<T>::P_FN fn>
struct PHelp
{
  template <typename OBJ_TYP>
  void operator()(OBJ_TYP* o) { (o->*fn)(); }
  template <typename OBJ_TYP>
  void operator()(OBJ_TYP& o) { (o.*fn)(); }
};

int main()
{
  PHelp<C, &C::printName> cHelp;
  PHelp<D, &D::print> dHelp;

  cHelp(&c);
  cHelp(c);

  dHelp(&d);
  dHelp(d);

  return 0;
}


