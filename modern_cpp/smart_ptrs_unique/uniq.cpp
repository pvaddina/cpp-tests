#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <array>

struct FooStruct
{
  FooStruct() = default;
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
    std::unique_ptr<FooStruct> p1;
    if (!p1) { std::cout << "p1 is not initialized" << std::endl; }

    std::unique_ptr<FooStruct> p2 { new FooStruct };
    if (p2) { std::cout << "p2 is initialized directly" << std::endl; }

    // make_shared usage
    std::unique_ptr<FooStruct> p3 = std::make_unique<FooStruct>();
    if (p3) { std::cout << "p3 is initialized using make_unique" << std::endl; }
    std::unique_ptr<FooStruct> p4 = std::make_unique<FooStruct>("Some rvalue string");
    if (p4) { std::cout << "p4 is initialized using make_unique with arguments" << std::endl; }
    std::cout << "p4->p=" << p4->p << ", p4->s=" << p4->s << std::endl;        

    // Array items
    std::unique_ptr<FooStruct[]> p5_array;
    if(!p5_array) {  std::cout << "p5 (array of FooStruct) is not initialized" << std::endl; }
    p5_array.reset( new FooStruct[3] );
    p5_array[0] = FooStruct { 1, "one" };
    p5_array[1] = FooStruct { 2, "two" };
    p5_array[2] = FooStruct { 3, "three" };

    auto p6_array = std::make_unique<FooStruct[]>(4);
    p6_array[0] = FooStruct { 1, "one" };
    p6_array[1] = FooStruct { 2, "two" };
    p6_array[2] = FooStruct { 3, "three" };
    p6_array[3] = FooStruct { 4, "four" };
  }
}


namespace T2
{
  void CusDelFunction(FooStruct* p)
  {
    std::cout << "In the custom deleter of FooStruct" << std::endl;
    delete p;
  }

  void Test()
  {
    std::cout << "In T2::Test" << std::endl;

    // A function as a custom destructor
    std::unique_ptr<FooStruct, decltype(&CusDelFunction)> p1 { new FooStruct, &CusDelFunction };


    // A Lambda as a custom destructor
    auto CusDelLambda = [](FooStruct* p) {
      std::cout << "In the custom deleter of FooStruct (auto)" << std::endl;
      delete p;
    };

    std::unique_ptr<FooStruct, decltype(CusDelLambda)> p2 { new FooStruct, CusDelLambda };
  }
}


namespace T3
{
  template <typename... Ts>
  std::unique_ptr<FooStruct> MakeFooStruct(Ts&&... args)
  {
    return std::unique_ptr<FooStruct>(new FooStruct(std::forward<Ts>(args)...));
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
  }
}



int main()
{
  T1::Test();
  std::cout << "\n";

  T2::Test();
  std::cout << "\n";

  T3::Test();
  return 0;
}
