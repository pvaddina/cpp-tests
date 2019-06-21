#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <functional>

namespace T1
{
  struct SomeStruct
  {
    SomeStruct(const SomeStruct&) { std::cout << "COPY CONSTRUCTOR" << std::endl; }
    SomeStruct& operator=(const SomeStruct&) { std::cout << "ASSIGNMENT OPERATOR" << std::endl; }
    SomeStruct(const int id, std::string&& s) : mId {id}, mName{s} {}
    void Print() const
    {
      std::cout << "mId=" << mId << ", mName=" << mName << std::endl;
    }
    void LambdaTest()
    {
      // Lambda capture test within a class: Capturing this without a reference
      std::cout << "\nLamdatest: Passing this directly\n================================" << std::endl;
      auto l = [this]() {
        std::cout << "Calling this->Print()" << std::endl;
        this->Print();
        std::cout << "Calling Print() without this" << std::endl;
        Print();
      };
      l();

      // Lambda capture test within a class: Capturing *this without a reference
      std::cout << "\nLamdatest: Passing *this directly\n================================" << std::endl;
      auto l1 = [*this]() {
        std::cout << "Calling Print() without this" << std::endl;
        Print();
      };
      l1();

      // Lambda capture test within a class: Passing everything within the scope as reference '&'
      std::cout << "\nLamdatest: Passing everything with '&'\n================================" << std::endl;
      auto l2 = [&]() {
        std::cout << "Calling this->Print()" << std::endl;
        this->Print();
        std::cout << "Calling Print() without this" << std::endl;
        Print();
      };
      l2();

      // Lambda capture test within a class: Capturing *this without a reference
      std::cout << "\nLamdatest: Passing everything with '='\n================================" << std::endl;
      auto l3 = [=]() {
        std::cout << "Calling this->Print(). Note no copy constructor called" << std::endl;
        this->Print();
        std::cout << "Calling Print() without this. Note no copy constructor called" << std::endl;
        Print();
      };
      l3();
    }
    private:
    int mId = 0;
    std::string mName = "invalid name";
  };

  void Test()
  {
    SomeStruct s {437, "Some kind of structure"};

    // Test-1: Pass everything as reference
    std::cout << "Test1\n======" << std::endl;
    auto l1 = [&]() {
      std::cout << "Test passing EVERYTHING in the scope as reference" << std::endl;
      s.Print();
    };
    l1();

    // Test-2: Pass everything as copy
    std::cout << "\nTest2\n======" << std::endl;
    auto l2 = [=]() {
      std::cout << "Test passing EVERYTHING in the scope as copy. Note the values of the object are set to the default" << std::endl;
      s.Print();
    };
    l2();

    // Test-3: Some tests of lambda usage within a class
    s.LambdaTest();
  }
}


namespace Pitfalls
{
  enum class Operation
  {
    ADD,
    ADD_FAIL,
    SUB,
    SUB_FAIL,
    MUL,
    MUL_FAIL
  };

  std::function<void()> DoOp(Operation op, int arg1, int arg2)
  {
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // All the following operations work as expected, since the arguments 'arg1' and 'arg2' are 
    // passed as values and not references
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if      (op == Operation::ADD)       { return [arg1, arg2]() { std::cout << "Addition of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1 + arg2 << std::endl; }; }
    else if (op == Operation::SUB)       { return [arg1, arg2]() { std::cout << "Subtraction of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1 - arg2 << std::endl; }; }
    else if (op == Operation::MUL)       { return [arg1, arg2]() { std::cout << "Multiplication of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1*arg2 << std::endl; }; }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // All the following operations FAIL to work as expected, since the arguments 'arg1' and 'arg2' are 
    // passed as references. And these references are only valid until end of the current scope, meaning
    // end of the current function, DoOp. 
    // But at the point when the closure is actually called, in the function, 'Test', the references
    // are no longer valid and will result in junk ouput
    ////////////////////////////////////////////////////////////////////////////////////////////////
    else if (op == Operation::ADD_FAIL)  { return [&arg1, &arg2]() { std::cout << "Addition of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1 + arg2 << std::endl; }; }
    else if (op == Operation::SUB_FAIL)  { return [&arg1, &arg2]() { std::cout << "Subtraction of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1 - arg2 << std::endl; }; }
    else if (op == Operation::MUL_FAIL)  { return [&arg1, &arg2]() { std::cout << "Multiplication of arg1=" << arg1 << ", and arg2=" << arg2 << ", is " << arg1*arg2 << std::endl; }; }
    else                                 { return [&arg1, &arg2]() { std::cout << "Nothing"; }; }
  }

  void Test()
  {
    std::cout << "\nPitfalls::Test: Testing a potential pitfall (Dangling references)'&'\n===========================================" << std::endl;

    DoOp(Operation::ADD, 1, 2)();        // Addition of arg1=1, and arg2=2, is 3
    DoOp(Operation::ADD_FAIL, 1, 2)();   // Addition of arg1=-1452375399, and arg2=32524, is -1452342875
    DoOp(Operation::SUB, 1, 2)();        // Subtraction of arg1=1, and arg2=2, is -1
    DoOp(Operation::SUB_FAIL, 1, 2)();   // Subtraction of arg1=-1452375399, and arg2=32524, is -1452407923
    DoOp(Operation::MUL, 1, 2)();        // Multiplication of arg1=1, and arg2=2, is 2
    DoOp(Operation::MUL_FAIL, 1, 2)();   // Multiplication of arg1=-1452375399, and arg2=32524, is -1007155668
  }
}


namespace T2
{
  void MutableCapture()
  {
    std::cout << "\nT2::MutableCapture: Testing mutable capture\n======================================" << std::endl;

    int ini_start = 0;
    std::vector<int> v(10);
    // 
    // Creating a lambda of the following type is like creating a class as below:
    // class some_compiler_generated_class_name
    // {
    //   public:
    //      void operator()() { return ++ini_start; } --> Note the function is not const, because the lambda is defined as mutable
    //   private: 
    //      int ini_start;
    // };
    // 
    auto initializer = [ini_start]() mutable { return ++ini_start; }; // Pass 'ini_start' as a MUTABLE value. 

    // Pass 'ini_start' as mutable value. So, one would expect every call to 'initializer' to return just '++ini_start', meaning 1. 
    // But given that defining a lambda will indirectly create a compiler generated class, as mentioned above, the call to an object of
    // this generated class, will update the 'ini_start' internally. This ultimately results in a unique_value on every call.
    std::generate(v.begin(), v.end(), initializer);
    std::cout << "Initialized values of vector: ";
    for(auto& item: v)
    {
      std::cout << item << " ";
    }
    std::cout << "\nNote: The value of ini_start is still the same as before, as it is passed by value not by reference to the lambda = " << ini_start << std::endl;
  }

  void ImmutableCapture()
  {
    std::cout << "\nT2::ImmutableCapture: Testing immutable capture\n======================================" << std::endl;

    int ini_start = 0;
    std::vector<int> v(10);
    // 
    // Creating a lambda of the following type is like creating a class as below:
    // class some_compiler_generated_class_name
    // {
    //   public:
    //      void operator()() const { return ini_start+324; } --> Note the function is const
    //   private: 
    //      int ini_start;
    // };
    // 
    auto initializer = [ini_start]() { return ini_start+324; };

    // 
    // Pass 'ini_start' as value. 
    // Given that defining a lambda will indirectly create a compiler generated class, as mentioned above, the call to an object of
    // this generated class, will simply return sum of 'ini_start+324' for every single call.
    // 
    std::generate(v.begin(), v.end(), initializer);
    std::cout << "Initialized values of vector: ";
    for(auto& item: v)
    {
      std::cout << item << " ";
    }
  }

}



int main()
{
  T1::Test();
  Pitfalls::Test();
  T2::MutableCapture();
  T2::ImmutableCapture();
  
  return 0;
}



