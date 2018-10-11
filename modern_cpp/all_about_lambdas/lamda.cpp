#include <iostream>

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
      std::cout << "Calling this->Print()" << std::endl;
      this->Print();
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
    std::cout << "Testing passing EVERYTHING in the scope as reference" << std::endl;
    s.Print();
  };
  l1();

  // Test-2: Pass everything as copy
  std::cout << "\nTest2\n======" << std::endl;
  auto l2 = [=]() {
    std::cout << "Testing passing EVERYTHING in the scope as copy. Note the values of the object are set to the default" << std::endl;
    s.Print();
  };
  l2();

  // Test-3: Some tests of lambda usage within a class
  s.LambdaTest();
}

int main()
{
  Test();
  return 0;
}



