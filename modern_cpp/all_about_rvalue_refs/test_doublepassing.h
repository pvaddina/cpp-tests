#include <iostream>
#include <string>
#include <vector>

namespace Test7
{
  struct SimpleData
  {
    int id = 437;
    std::string name = "default name";
    // Note since there is a constructor which takes rvalue references, the constructor with const references is not called for rvalues
    SimpleData(const int& _v, const std::string& _s) : id(_v), name(_s) { std::cout << "Constructor with const references" << std::endl; }
    SimpleData(int&& _v, std::string&& _s) : id(_v), name(_s) { std::cout << "Constructor with rvalue references" << std::endl;  }
    // Move constructor
    // Deliberately deleting:
    // 1. copy constructor
    // 2. copy assignment operator
    // 3. move constructor
    // 4. move assignment operator
    SimpleData(const SimpleData&) = delete;
    SimpleData& operator=(SimpleData&) = delete;
    SimpleData& operator=(SimpleData&& msg) = delete;
    SimpleData(SimpleData&& msg) = delete;

    void Print() const { std::cout << "Id=" << id << ", Name=" << name << std::endl; }
  };

  void LvalueAcceptor(SimpleData& sd)
  {
    sd.Print();
  }

  void RvalueAcceptor(SimpleData&& sd)
  {
    LvalueAcceptor(sd);
  }

  void Test_DoublePassing()
  {
    RvalueAcceptor(SimpleData{437, "Roll number"});
  }
}

