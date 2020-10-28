#include <string>
#include <vector>
#include <iostream>

namespace C
{
  struct Foo
  {
    Foo() = default;
    Foo(const int& i, const std::string& s) : id(i), name(s) { std::cout << "In Foo constructor\n"; }
    Foo(const Foo& f) { std::cout << "In Foo copy constructor\n"; id = f.id; name = f.name; }
    friend std::ostream& operator<<(std::ostream& o, const Foo& f);
  private:
    int id = {};
    std::string name = {};
  };

  std::ostream& operator<<(std::ostream& o, const Foo& f)
  {
    o << "Foo::id=" << f.id << ", Foo::name=" << f.name;
    return o;
  }

  class Base
  {
  public:
    Base(int&& i, std::string&& s) : mIntVal(std::move(i)), mStrVal(std::move(s)) {}
    Base(const Base& b) : mIntVal(b.mIntVal), mStrVal(b.mStrVal) {}
    virtual void Print() { std::cout << "Base::mIntVal=" << mIntVal << ", Base::mStrVal=" << mStrVal; }

  private:
    int mIntVal;
    std::string mStrVal;
  };

  class DefaultedCopyCons : public Base
  {
  public:
    DefaultedCopyCons(int&& i, std::string&& s, std::string&& s1) : Base(std::move(i), std::move(s)), mVec{ 2,4,6,8,10,12 }, mDer(std::move(s1)), mFooObj{ 590485, "Antarctica" } {}
    DefaultedCopyCons(const DefaultedCopyCons&) = default; // With or without a defaulted copy constructor the Foo object will be copied accordingly
    void Print() override {
      Base::Print();
      std::cout << ", DefaultedCopyCons::mVec=";
      for (auto& v : mVec) { std::cout << v << " "; }
      std::cout << ", DefaultedCopyCons::mDer=" << mDer << ", " << mFooObj;
    }

  private:
    std::vector<int> mVec;
    std::string mDer = "";
    Foo mFooObj;
  };

  class NoCopyCons : public Base
  {
  public:
    NoCopyCons(int&& i, std::string&& s, std::string&& s1) : Base(std::move(i), std::move(s)), mVec{ 2,4,6,8,10,12 }, mDer(std::move(s1)), mFooObj{ 590485, "Antarctica" } {}
    void Print() override {
      Base::Print();
      std::cout << ", NoCopyCons::mVec=";
      for (auto& v : mVec) { std::cout << v << " "; }
      std::cout << ", NoCopyCons::mDer=" << mDer << ", " << mFooObj;
    }

  private:
    std::vector<int> mVec;
    std::string mDer = "";
    Foo mFooObj;
  };

  void TestCopyConstructorWithInheritence()
  {
    std::cout << "############################## In TestCopyConstructorWithInheritence\n";

    {
      std::cout << "================= Base Test =================================\n";
      // Base tests
      Base one{ 437, "string 437" };
      Base two(one);

      one.Print();
      std::cout << std::endl;
      two.Print();
      std::cout << std::endl;
    }

    {
      std::cout << "================= DefaultedCopyCons Test =================================\n";
      // Der tests
      DefaultedCopyCons dOne{ 111, "string 111", "derived string 111" };
      dOne.Print();
      std::cout << std::endl;

      DefaultedCopyCons dTwo(dOne);
      dTwo.Print();
      std::cout << std::endl;
    }

    {
      std::cout << "============ NoCopyCons Test ======================================\n";
      // Der tests
      NoCopyCons dOne{ 222, "string 222", "derived string 222" };
      dOne.Print();
      std::cout << std::endl;

      NoCopyCons dTwo(dOne);
      dTwo.Print();
      std::cout << std::endl;
    }
  }
}

