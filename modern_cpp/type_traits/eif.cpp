#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

namespace T1
{
  template <typename T>
  struct TA
  {
    void Print() { std::cout << val << std::endl; }
    T val;
  };

  // A special kind of initialization only for integers. 
  template <typename T>
  void Init(TA<typename std::enable_if<std::is_same<T, int>::value, T>::type>& obj)
  {
    obj.val = 437;
  }

  void Test()
  {
    std::cout << "*********************** T1::Test\n";
    TA<int> m1;
    TA<std::string> m2;
    /// Note the explicit specialization of the template parameter is necessary without which
    /// the compiler cannot deduce the type for 'T' and will result in error
    Init<int>(m1);
    m1.Print();
  }
}

namespace T2
{
  struct C1 { void logdata() { std::cout << "C1" << std::endl; } };
  struct C2 { void someprint() { std::cout << "C2" << std::endl; } };

  template <typename T>
  struct CommonPrinter
  {
    template <typename T1 = T>
    typename std::enable_if_t<std::is_same_v<T1,C1>,void>
    Print() { val.logdata(); }

    template <typename T2 = T>
    typename std::enable_if_t<std::is_same_v<T2,C2>,void>
    Print() { val.someprint(); }

    T val;
  };

  void Test()
  {
    std::cout << "*********************** T2::Test\n";
    CommonPrinter<C1> c1;
    c1.Print();

    CommonPrinter<C2> c2;
    c2.Print();
  }
}

namespace T3
{
  template<bool VAL>
  struct Direction
  {
    template<bool IN=VAL> 
    typename std::enable_if<IN>::type Print() { std::cout << "In direction\n"; }

    template<bool IN=VAL> 
    typename std::enable_if<!IN>::type Print() { std::cout << "Out direction\n"; }
  };

  void Test()
  {
    std::cout << "*********************** T3::Test\n";
    Direction<true> in;
    Direction<false> out;
    in.Print();
    out.Print();
  }
}


int main()
{
  T1::Test();
  T2::Test();
  T3::Test();
  return 0;
}



