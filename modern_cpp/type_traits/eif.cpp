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
    TA<int> m1;
    TA<std::string> m2;
    /// Note the explicit specialization of the template parameter is necessary without which
    /// the compiler cannot deduce the type for 'T' and will result in error
    Init<int>(m1);
    m1.Print();
  }
}

#if 0
namespace T2
{
  template <typename T>
  struct TA
  {
    void Print() { std::cout << val << std::endl; }
    T val;
  };

  // A special kind of initialization only for integers. 
  template<typename<class> class P>
  void Init(P& obj)
  {
    obj.val = 437;
  }

  void Test()
  {
    TA<int> m1;
    TA<std::string> m2;
    /// Note the explicit specialization of the template parameter is necessary without which
    /// the compiler cannot deduce the type for 'T' and will result in error
    Init(m1);
    m1.Print();
  }
}
#endif

namespace T3
{
  template<bool VAL>
  struct Direction
  {
    template<bool IN=VAL> 
    typename std::enable_if<IN>::type Print() { std::cout << "In direction\n" << std::endl; }

    template<bool IN=VAL> 
    typename std::enable_if<!IN>::type Print() { std::cout << "Out direction\n" << std::endl; }
  };

  void Test_Direction()
  {
    Direction<true> in;
    Direction<false> out;
    in.Print();
    out.Print();
  }
}


int main()
{
  T1::Test();
  //T2::Test();
  T3::Test_Direction();
  return 0;
}



