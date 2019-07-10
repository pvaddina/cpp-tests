#include <iostream>
#include <string>
#include <vector>

namespace Test6
{
  struct SimpleData
  {
    int id = 437;
    std::string name = "default name";
    // Note since there is a constructor which takes rvalue references, the constructor with const references is not called for rvalues
    SimpleData(const int& _v, const std::string& _s) : id(_v), name(_s) { std::cout << "Constructor with const references" << std::endl; }
    SimpleData(int&& _v, std::string&& _s) : id(_v), name(_s) { std::cout << "Constructor with rvalue references" << std::endl;  }
    // Move constructor
    SimpleData(SimpleData&& msg)
    {
      id = msg.id;
      name = std::move(msg.name);
    }

    // Deliberately deleting:
    // 1. copy constructor
    // 2. copy assignment operator
    // 3. move assignment operator
    SimpleData(const SimpleData&) = delete;
    SimpleData& operator=(SimpleData&) = delete;
    SimpleData& operator=(SimpleData&& msg) = delete;

    void Print() const { std::cout << "Id=" << id << ", Name=" << name << std::endl; }
  };

  struct WrapperWithMove
  {
    // Note: The struct in the current form (explicitly defining the move construction) 
    // will automatically result in a deleted copy constructor
    WrapperWithMove(SimpleData&& in) : val(std::move(in)) {}
                                          //    ^
                                          //    |
                                          //    ------ Call Move constructor: SimpleData(SimpleData&&)
    const SimpleData val;
    void Print() { val.Print(); }
  };

  struct WrapperWithForward
  {
    // Note: The struct in the current form (explicitly defining the move construction) 
    // will automatically result in a deleted copy constructor
    WrapperWithForward(SimpleData&& in) : val(std::forward<SimpleData>(in)) {}
                                                      //    ^
                                                      //    |
                                                      //    ------ Call Move constructor: SimpleData(SimpleData&&)
    const SimpleData val;
    void Print() { val.Print(); }
  };


  void Test_CopyEffects()
  {
    // Trying to construct an object as below will create a Wrapper object first and the 
    // object 'one' is copy constructed using the temporary (as opposed to copy assigned)
    // auto one = WrapperWithMove{ {111, "One" } };
    // WrapperWithMove one = Wrapper{ {111, "One" } };

    // Here no temporary Wrapper objects are created. A "SimpleData" object
    // is created and passed to the constructor which takes rvalue references
    WrapperWithMove one = { {111, "One" } };
    WrapperWithMove two{ {222, "Two" } };
    WrapperWithForward three{ { 333, "Three"} };

    one.Print();
    two.Print();
    three.Print();
  }
}

