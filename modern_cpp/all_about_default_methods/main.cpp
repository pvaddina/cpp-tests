#include <iostream>
#include <string>


namespace T1
{
  struct S1
  {
    public:
      bool operator==(const S1& rhs) const { return (id==rhs.id) && (name==rhs.name); }
    private:
      int id;
      std::string name;
  };

  class Foo
  {
    public:
      Foo() = default;
      ~Foo() = default;
      Foo(const Foo&) = default;
      Foo(Foo&&) = default;
      bool operator==(const Foo& rhs) { return (mS1==rhs.mS1) && (mIndex==rhs.mIndex); }

    private:
      S1 mS1;
      int mIndex;
  };

  void Test()
  {
    std::cout << "####################################### Test-1: Demonstrate aliasing global function\n";
  }
}

int main()
{
  T1::Test();
  return 0;
}



