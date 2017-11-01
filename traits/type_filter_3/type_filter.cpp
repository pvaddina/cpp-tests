#include <iostream>

struct A { void OPrint() { std::cout << "In A" << std::endl; } };
struct B { void OPrint() { std::cout << "In B" << std::endl; } };
struct C { void OPrint() { std::cout << "In C" << std::endl; } };
struct D { void OPrint() { std::cout << "In D" << std::endl; } };
struct E { void OPrint() { std::cout << "In E" << std::endl; } };
struct F { void OPrint() { std::cout << "In F" << std::endl; } };
struct G { void OPrint() { std::cout << "In G" << std::endl; } };
struct NONE { void OPrint() { std::cout << "In NONE" << std::endl; } };

template <typename T> struct Msg{ typedef T TYP; };
template <> struct Msg<A>{ typedef A TYP; };
template <> struct Msg<B>{ typedef B TYP; };
template <> struct Msg<C>{ typedef C TYP; };
template <> struct Msg<D>{ typedef D NO_TYP; };
template <> struct Msg<E>{ typedef E NO_TYP; };
template <> struct Msg<F>{ typedef F TYP; };
template <> struct Msg<G>{ typedef G TYP; };

template <typename T>
void print(typename Msg<T>::TYP& msg)
{
  msg.OPrint();
}

template <typename T>
void print(typename Msg<T>::NO_TYP& msg)
{
  std::cout << "In the other print" << std::endl;
  msg.OPrint();
}

int main()
{
  A a;
  B b;
  C c;
  D d;
  E e;
  F f;
  G g;

  print<A>(a);
  print<B>(b);
  print<C>(c);
  print<D>(d);
  print<E>(e);
  print<F>(f);
  print<G>(g);

  return 0;
}

