#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <array>

struct CopyableFooStruct
{
  CopyableFooStruct() = default;
  CopyableFooStruct(const CopyableFooStruct&) = delete;
  //CopyableFooStruct& operator=(const CopyableFooStruct&) = delete;
  CopyableFooStruct(std::string&& _s) : s(_s) {}
  CopyableFooStruct(int i, std::string&& _s) : p(i), s(_s) {}
  int p { 437 };
  std::string s { "Some test string" };
  void Print() { std::cout << "p = " << p << ", s=" << s << std::endl; }
};

struct FooStruct
{
  FooStruct() = default;
  FooStruct(const FooStruct&) = delete;
  FooStruct& operator=(const FooStruct&) = delete;
  FooStruct(std::string&& _s) : s(_s) {}
  FooStruct(int i, std::string&& _s) : p(i), s(_s) {}
  int p { 437 };
  std::string s { "Some test string" };
  void Print() { std::cout << "p = " << p << ", s=" << s << std::endl; }
};

// A simple test to show the use of constexpr members within a class
namespace T1
{
  void Test()
  {
    std::cout << "In T1::Test" << std::endl;

    // Can be used for logical operations
    std::unique_ptr<CopyableFooStruct> p1;
    if (!p1) { std::cout << "p1 is not initialized" << std::endl; }

    std::unique_ptr<CopyableFooStruct> p2 { new CopyableFooStruct };
    if (p2) { std::cout << "p2 is initialized directly" << std::endl; }

    // make_shared usage
    std::unique_ptr<CopyableFooStruct> p3 = std::make_unique<CopyableFooStruct>();
    if (p3) { std::cout << "p3 is initialized using make_unique" << std::endl; }
    std::unique_ptr<CopyableFooStruct> p4 = std::make_unique<CopyableFooStruct>("Some rvalue string");
    if (p4) { std::cout << "p4 is initialized using make_unique with arguments" << std::endl; }
    std::cout << "p4->p=" << p4->p << ", p4->s=" << p4->s << std::endl;        

    // Array items
    std::unique_ptr<CopyableFooStruct[]> p5_array;
    if(!p5_array) {  std::cout << "p5 (array of CopyableFooStruct) is not initialized" << std::endl; }
    p5_array.reset( new CopyableFooStruct[3] );
    p5_array[0] = CopyableFooStruct { 1, "one" };   // Assignment operator called. A new CopyableFooStruct is being assigned
    p5_array[1] = CopyableFooStruct { 2, "two" };   // Assignment operator called. A new CopyableFooStruct is being assigned
    p5_array[2] = CopyableFooStruct { 3, "three" }; // Assignment operator called. A new CopyableFooStruct is being assigned

    auto p6_array = std::make_unique<CopyableFooStruct[]>(4);
    p6_array[0] = CopyableFooStruct { 1, "one" };   // Assignment operator called. A new CopyableFooStruct is being assigned
    p6_array[1] = CopyableFooStruct { 2, "two" };   // Assignment operator called. A new CopyableFooStruct is being assigned
    p6_array[2] = CopyableFooStruct { 3, "three" }; // Assignment operator called. A new CopyableFooStruct is being assigned
    p6_array[3] = CopyableFooStruct { 4, "four" };  // Assignment operator called. A new CopyableFooStruct is being assigned
  }
}


namespace T2
{
  void CusDelFunction(CopyableFooStruct* p)
  {
    std::cout << "In the custom deleter of CopyableFooStruct" << std::endl;
    delete p;
  }

  void Test()
  {
    std::cout << "In T2::Test" << std::endl;

    // A function as a custom destructor
    std::unique_ptr<CopyableFooStruct, decltype(&CusDelFunction)> p1 { new CopyableFooStruct, &CusDelFunction };

    // A Lambda as a custom destructor
    auto CusDelLambda = [](CopyableFooStruct* p) {
      std::cout << "In the custom deleter of CopyableFooStruct (auto)" << std::endl;
      delete p;
    };

    std::unique_ptr<CopyableFooStruct, decltype(CusDelLambda)> p2 { new CopyableFooStruct, CusDelLambda };
  }
}


namespace T3
{
  template <typename... Ts>
  std::unique_ptr<CopyableFooStruct> MakeFooStruct(Ts&&... args)
  {
    return std::unique_ptr<CopyableFooStruct>(new CopyableFooStruct(std::forward<Ts>(args)...));
  }

  template <typename T, typename... Ts>
  std::unique_ptr<T> MakeAnyStruct(Ts&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
  }

  void Test()
  {
    std::cout << "In T3::Test" << std::endl;

    auto p1 = MakeFooStruct();
    p1->Print();

    auto p2 = MakeFooStruct(std::string("Only one argument"));
    p2->Print();

    auto p3 = MakeFooStruct(444, std::string("Two arguments"));
    p3->Print();

    auto p4 = MakeAnyStruct<CopyableFooStruct>();
    p4->Print();

    auto p5 = MakeAnyStruct<CopyableFooStruct>(std::string("Only one argument"));
    p5->Print();

    auto p6 = MakeAnyStruct<CopyableFooStruct>(444, std::string("Two arguments"));
    p6->Print();
  }
}


namespace T4
{
#if 0
  template <typename T, typename... Ts>
  std::unique_ptr<T> MakeAnyStruct(Ts&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
  }

  template <typename... Ts>
  using MakeFooStruct = MakeAnyStruct<CopyableFooStruct, Ts...>;

  void Test()
  {
    std::cout << "In T4::Test" << std::endl;

    auto p1 = MakeFooStruct();
    p1->Print();

    auto p2 = MakeFooStruct(std::string("Only one argument"));
    p2->Print();

    auto p3 = MakeFooStruct(444, std::string("Two arguments"));
    p3->Print();

    auto p4 = MakeAnyStruct();
    p1->Print();

    auto p5 = MakeAnyStruct(std::string("Only one argument"));
    p2->Print();

    auto p6 = MakeAnyStruct(444, std::string("Two arguments"));
    p3->Print();
  }
#endif
}


namespace T5
{
  template <typename T, typename... Ts>
  std::unique_ptr<T> MakeAnyStruct(Ts&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
  }

  void Test()
  {
    std::cout << "In T5::Test" << std::endl;

    std::vector<std::unique_ptr<FooStruct> > v;
    v.push_back(MakeAnyStruct<FooStruct>());
    v.push_back(MakeAnyStruct<FooStruct>("Some string"));
    v.push_back(MakeAnyStruct<FooStruct>(46354, "Another String"));

    auto i = 0;
    for (auto& iter : v)
    { 
      std::cout << i++ << ".";
      iter->Print();
    }

    // auto p = v[0];  // Compilation error. Use of deleted copy constructor 
    auto movedP = std::move(v[0]); // Fine. This is constructed with move semantics. Allowed.
    i = 0;
    for (auto& iter : v)
    {
      std::cout << i++ << ".";
      if (iter)
        iter->Print();
      else
        std::cout << "<<<<<< Invalid index >>>>>>>>" << std::endl;
    }
    std::cout << "Printing contents of movedP: ";
    movedP->Print();
  }
}


int main()
{
  T1::Test();
  std::cout << "\n";

  T2::Test();
  std::cout << "\n";

  T3::Test();
  std::cout << "\n";

  T5::Test();
  return 0;
}
