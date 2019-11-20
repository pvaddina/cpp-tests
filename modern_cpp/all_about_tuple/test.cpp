#include <iostream>
#include <string>
#include <vector>
#include <tuple>

namespace T1
{
  using T1Typ = std::tuple<std::string, std::vector<int>, std::vector<int>&>;

  void print_vec(const std::vector<int>& v)
  {
    for (auto& it : v)
      std::cout << it << " ";
    std::cout << std::endl;
  }

  void print_mytyp(const std::string&& s, const T1Typ& v)
  {
    std::cout << s << std::endl;
    std::cout << std::get<0>(v) << std::endl;
    print_vec(std::get<1>(v));
    print_vec(std::get<2>(v));
  }

  void Test()
  {
    std::cout << "##################### Test-1: Demonstrate effect of move on referenced values in a tuple" << std::endl;

    std::vector<int> v { 1, 2, 3, 4, 5 };
    std::cout << "\nPrint the vector before any move operation: ";
    print_vec(v);
    T1Typ typ { "Simple String", {9,8,7,6}, std::ref(v) };
    print_mytyp("\nPrinting the tuple right after creation", typ);

    T1Typ typ2 = std::move(typ);
    print_mytyp("\ntyp2=move(typ): Printing 'typ' after the move (Notice 'v' is still valid, as passed by reference')", typ);
    print_mytyp("\ntyp2=move(typ): Printing 'typ2' after the move (Notice 'v' is still valid, as passed by reference')", typ2);

    std::cout << "\nPrint the vector after all the move operations(should remain unchanged as passed by reference only): ";
    print_vec(v);

    std::cout << "\nChanging v[2]=437, and notice the tuples\n";
    v[2] = 437;
    print_vec(v);
    print_mytyp("\nValue of 'typ' after move and value change", typ);
    print_mytyp("\nValue of 'typ2' after move and value change", typ2);
  }
}


namespace T2
{
  // A tuple type with a reference to an integer as one of its members. 
  using T2Typ = std::tuple<int&>;
  static int gValue = 437;

  // A simple wrapper structure for the type, 'T2Typ'
  struct Foo
  {
    // NOTE: Two constructors. One with no-argument and the other with an argument. 
    // And observe that even if the default constructor(one with no arguments), is no where 
    // used, the program will not compile
    // Therefore, enabling this constructor will not compile the program
    // Foo() {} 

    // To make it compile we need to implement the default constructor properly by initializing the member
    // variable, 'mVal' as it takes a reference. For example the following would work.
    Foo() : mVal{gValue} { std::cout << "Default constructor\n";}
    Foo(int* refVal) : mVal{*refVal} { std::cout << "Constructor with argument\n"; }
    void Print() const { std::cout << "mVal = " << std::get<0>(mVal) << std::endl; }
    private:
      T2Typ mVal;
  };

  void Test()
  {
    std::cout << "##################### Test-2: Demonstrate using a tuple with a reference, as a member variable" << std::endl;
    int v = 999;
    Foo f (&v);
    f.Print();

    std::cout << "\n";

    Foo q;
    q.Print();
  }
}


namespace T3
{
  struct SimplePrinter
  {
    using PTuple = std::tuple<void(SimplePrinter::*)(std::string&&), void(SimplePrinter::*)(std::string&&)>;
    PTuple GetPrinters() const { return std::make_tuple(&SimplePrinter::DebugPrint, &SimplePrinter::ErrorPrint); }
  private:
    void DebugPrint(std::string&& s) { std::cout << "DebugPrint of SimplePrinter" << s << "\n"; }
    void ErrorPrint(std::string&& s) { std::cout << "ErrorPrint of SimplePrinter" << s << "\n"; }
    int someValue;
  };

  struct FancyPrinter
  {
    using PTuple = std::tuple<void(FancyPrinter::*)(std::string&&), void(FancyPrinter::*)(std::string&&)>;
    PTuple GetPrinters() const { return std::make_tuple(&FancyPrinter::DebugPrint, &FancyPrinter::ErrorPrint); }
  private:
    void DebugPrint(std::string&& s) { std::cout << "DebugPrint of FancyPrinter" << s << "\n"; }
    void ErrorPrint(std::string&& s) { std::cout << "ErrorPrint of FancyPrinter" << s << "\n"; }
    int someValue;
  };

  template <typename C, typename TP>
  void AnyPrint(C& obj, TP&& fs, std::string&& s)
  {
    auto f1 = std::get<0>(fs);
    auto f2 = std::get<1>(fs);
    (obj.*f1)(std::move(s));
    (obj.*f2)(std::move(s));
    //*(std::get<0>(fs))(std::move(s));
    //*(std::get<1>(fs))(std::move(s));
  }

  void Test()
  {
    std::cout << "##################### Test-3: Demonstrate passing a class member variable/method as reference to a function\n";
    // Trying out the SimplePrinter
    SimplePrinter sp;
    AnyPrint(sp, sp.GetPrinters(), ": Testing SimplePrinter");

    // Now try out the FancyPrinter
    FancyPrinter fp;
    AnyPrint(fp, fp.GetPrinters(), ": Testing FancyPrinter");
  }
}

int main()
{
  T1::Test();
  T2::Test();
  T3::Test();
  return 0;
}
