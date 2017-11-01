#include <iostream>

template <bool ONE, bool TWO>
struct MsgTraits
{
  static bool Prop1() { return ONE; }
  static bool Prop2() { return TWO; }
};

class A {};
class B {};
class C {};
class D {};
class E {};
class F {};
class G {};

template <typename T> struct Msg{ typedef T MSG; static MsgTraits<false,false> PROPS; };
template <> struct Msg<A>{ typedef A MSG; static MsgTraits<true,false> PROPS; };
template <> struct Msg<B>{ typedef B MSG; static MsgTraits<true,true> PROPS; };
template <> struct Msg<F>{ typedef F MSG; static MsgTraits<false,true> PROPS; };

template <typename T>
void print(T& msg)
{
  std::cout << "Prop1=" << Msg<T>::PROPS.Prop1() << ", Prop2=" << Msg<T>::PROPS.Prop2() << std::endl;
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

