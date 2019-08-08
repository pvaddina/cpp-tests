#include <iostream>
#include <variant>
#include <string>
#include <type_traits>
#include <vector>


template <typename T>
struct DType
{
  DType()                      { std::cout << "**In default constructor:v=" << v << std::endl; }
  DType(const T& _v) : v(_v)   { std::cout << "**Constructing with value=" << v << std::endl; }
  DType(const DType& t)        { std::cout << "**In Copy constructor with value=" << t.v << std::endl; v = t.v; }
  ~DType()                     { std::cout << "**Destroying the object with value=" << v << std::endl;  }
  void Print() const           { std::cout << "Current Value = " << v << std::endl; }
  void Set(T _v)               { v = _v; }
  private:
  T v;
};

using IntTyp = DType<int>;
using StrTyp = DType<std::string>;
using DoubTyp = DType<double>;
typedef std::variant<IntTyp, StrTyp, DoubTyp> MyTyp;

namespace T1
{
  void IntTypTester(MyTyp& t)
  {
    t = IntTyp(456);
    std::get<IntTyp>(t).Print();
  }

  void StrTypTester(MyTyp& t)
  {
    t = StrTyp("This is a string");
    std::get<StrTyp>(t).Print();
  }

  void DoubTypTester(MyTyp& t)
  {
    t = DoubTyp(456.435);
    std::get<DoubTyp>(t).Print();
  }

  void SimpleTests()
  {
    std::cout << "########################## SimpleTests" << std::endl;
    MyTyp t1;
    std::cout << "t1 is now (default) initialized. Passing it over to IntTypTester" << std::endl;
    IntTypTester(t1);

    std::cout << "\n";
    MyTyp t2;
    std::cout << "t2 is now (default) initialized. Passing it to StrTypTester." << std::endl;
    StrTypTester(t2);

    std::cout << "\n";
    MyTyp t3;
    std::cout << "t3 is now (default) initialized. Passing it to DoubTypTester." << std::endl;
    DoubTypTester(t3);
  }


  void ReassignTests()
  {
    std::cout << "\n########################## ReassignTests: Reassigning the same variable with different values also works." << std::endl;
    MyTyp t;
    std::cout << "t is now (default) initialized. Assigning it an IntTyp" << std::endl;
    t = IntTyp(456);
    std::get<IntTyp>(t).Print();

    std::cout << "\nAssigning an StrTyp to t" << std::endl;
    t = StrTyp("This is a string");
    std::get<StrTyp>(t).Print();

    std::cout << "\nAssigning an DoubTyp to t" << std::endl;
    t = DoubTyp(456.435);
    std::get<DoubTyp>(t).Print();
  }
}

namespace T2
{
  struct CustomStrTyp : public StrTyp
  {
    CustomStrTyp(std::string s) : StrTyp(s) {}
    void PrintCustomMsg() { std::cout << "In CustomStrTyp" << std::endl; }
  };

  typedef std::variant<IntTyp, StrTyp, DoubTyp, CustomStrTyp> FooMyTyp;


  template<class T> struct always_false : std::false_type {};

  // The following definition is lifted from the following link:
  // https://en.cppreference.com/w/cpp/utility/variant/visit
  auto MyTypProcessor = [](auto&& t) {
    using AT = std::decay_t<decltype(t)>;

    if constexpr (std::is_same_v<AT,IntTyp>) {
      std::cout << "Processing a IntTyp" << std::endl;
      t.Print();
    } else if constexpr (std::is_same_v<AT,StrTyp>) {
      std::cout << "Processing a StrTyp" << std::endl;
      t.Print();
    } else if constexpr (std::is_same_v<AT,CustomStrTyp>) {
      std::cout << "Processing a CustomStrTyp" << std::endl;
      t.Print();
      t.PrintCustomMsg();
    } else if constexpr (std::is_same_v<AT,DoubTyp>) {
      std::cout << "Processing a DoubTyp" << std::endl;
      t.Print();
    } else {
      static_assert(always_false<AT>::value, "non-exhaustive visitor!");
    }
  };


  void LambdaProcessing()
  {
    std::cout << "\n########################## LambdaProcessing: Process the variant type object using a lambda." << std::endl;

    FooMyTyp t;

    std::cout << "\nAssigning t, an IntTyp and processing it." << std::endl;
    t = IntTyp(456);
    std::visit(MyTypProcessor, t);

    std::cout << "\nAssigning t, an CustomStrTyp and processing it." << std::endl;
    t = CustomStrTyp("This is a string");
    std::visit(MyTypProcessor, t);

    std::cout << "\nAssigning t, an DoubTyp and processing it." << std::endl;
    t = DoubTyp(456.435);
    std::visit(MyTypProcessor, t);
  }
}

int main()
{
  T1::SimpleTests();
  T1::ReassignTests();
  T2::LambdaProcessing();
}
