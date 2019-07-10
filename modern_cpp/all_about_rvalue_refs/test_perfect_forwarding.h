#include <memory>
#include <string>
#include <iostream>

namespace Test10
{
  struct StrWrapper
  {
    StrWrapper(std::string&& _s) : s{_s} {}
    StrWrapper(const StrWrapper& _inStrWrapper) : s {_inStrWrapper.s } { std::cout << "StrWrapper: In copy constructor" << std::endl; }
    StrWrapper(StrWrapper&& _inStrWrapper) : s {std::move(_inStrWrapper.s) } { std::cout << "StrWrapper: In move constructor" << std::endl; }
    std::string s;
  };

  class Foo
  {
    public:
      Foo(const StrWrapper& inS, const int _id) : name(inS), id(_id) { std::cout << "Foo: In lvalue constructor" << std::endl; }
      Foo(StrWrapper&& inS, int&& _id) : name(std::move(inS)), id(_id) { std::cout << "Foo: In rvalue constructor" << std::endl; }
      void Print() { std::cout << "Name:" << name.s << ", id=" << id << std::endl; }
    private:
      StrWrapper name;
      int id;
  };

  // The only difference between Foo and NoConstFoo is the lvalue constructor which takes non-const arguments, in the case of NoConstFoo
  class NoConstFoo
  {
    public:
      NoConstFoo(StrWrapper& inS, int _id) : name(inS), id(_id) { std::cout << "NoConstFoo: In lvalue constructor" << std::endl; }
      NoConstFoo(StrWrapper&& inS, int&& _id) : name(std::move(inS)), id(_id) { std::cout << "NoConstFoo: In rvalue constructor" << std::endl; }
      void Print() { std::cout << "Name:" << name.s << ", id=" << id << std::endl; }
    private:
      StrWrapper name;
      int id;
  };

  class Coo
  {
    public:
      Coo(StrWrapper& inS, int _id) : name(inS), id(_id) { std::cout << "Coo: In lvalue constructor" << std::endl; }
      void Print() { std::cout << "Name:" << name.s << ", id=" << id << std::endl; }
    private:
      StrWrapper name;
      int id;
  };


  namespace Problem
  {
      template <typename ARG1, typename ARG2>
      Foo* CreateFoo(const ARG1& arg1, const ARG2& arg2)
      {
        return new Foo(arg1, arg2);
      }

      template <typename ARG1, typename ARG2>
      Coo* CreateCoo(ARG1& arg1, ARG2& arg2)
      {
        return new Coo(arg1, arg2);
      }

      void TestProblem()
      {
        std::cout << "\nIn Problem::TestProblem()\n";
        StrWrapper s { "FooObject" };
        int lclId = 2;
        std::cout << "====================================================================================================\n";
        std::cout << "Note: Problems mentioned here are related to \'Perfect Forwarding\'. Meaning, forward lvalues as \nlvalues (both const and non-const) and rvalues as rvalues. Therefore, these examples are based \non the fact that a factory method is used for the creation of Foo and Coo" << std::endl;
        std::cout << "====================================================================================================\n";
        std::cout << "********** Problem-1: Can only accept lvalues" << std::endl;

        // 
        // Problem-1: The factory method when NOT accepting const arguments as 'CreateCoo' does, can only be called with lvalues. rvalues cannot be passed.
        //
        std::unique_ptr<Coo> c1 { CreateCoo(s, lclId) }; // Passing lvalues
        c1->Print();
        //
        // Passing rvalues to the factory is NOT-OK.
        // The following initializations are not going to work
        // 
        //std::unique_ptr<Coo> c2 { CreateCoo(StrWrapper("Rvalue string"), lclId) };
        //std::unique_ptr<Coo> c3 { CreateCoo(s, 437) };
        //std::unique_ptr<Coo> c4 { CreateCoo(StrWrapper("Rvalue string"), 437) };

        std::cout << "********** Problem-2: Cannot use the factory to reach constructors taking rvalue references. Meaning even when an rvalue constructor is defined, it is unreachable." << std::endl;
        // 
        // Problem-2: If there is a constructor taking rvalue references, we can never reach it
        // Note that 'class Foo' has an rvalue constructor. But irrespective of how we call the factory
        // method, we can never reach that constructor. Note that the factory needs to take 'const' 
        // arguments for it to compile and take const lvalues and const rvalues
        std::unique_ptr<Foo> f1 { CreateFoo(s, lclId) };
        f1->Print();

        // 
        // Note: The factory method, 'CreateFoo' and the lvalue constructor of 'Foo' has to accept const 
        // arguments, without which we cannot create 'f2' using rvalues. This also introduces unnecessary 
        // issue of the passed arguments being always const and cannot be altered in anyway.
        // 
        std::unique_ptr<Foo> f2 { CreateFoo(StrWrapper("Rvalue string"), 437) };
        f2->Print();
      }
  }


  namespace Solution
  {
      // Note that in the call to Create the references are collapsed accordingly
      template <typename C, typename... ARGS>
      C* Create(ARGS&&... args)
      {
        return new C(std::forward<ARGS>(args)...);
      }

      void TestSolution()
      {
        std::cout << "\nIn Solution::TestSolution()\n";

        StrWrapper s { "FooObject" };
        int lclId = 2;
        
        // Note that despite Foo having a const lvalue and rvalue constructors, the compiler correctly chooses the right constructor
        // based on what is passed. 
        // In this case, the lvalue constructor is called
        std::cout << "\nCreating Foo ...\n";
        std::unique_ptr<Foo> f1 { Create<Foo>(s, lclId) };
        f1->Print();

        // In this case, the rvalue constructor is called, despite having a constructor which takes const arguments
        std::unique_ptr<Foo> f2 { Create<Foo>(StrWrapper("Rvalue string"), 437) };
        f2->Print();

        std::cout << "\nCreating NoConstFoo ...\n";
        // In this case of creation of NoConstFoo objects unsurprisingly the following two variants call the lvalue and rvalue
        // constructor accordingly
        std::unique_ptr<NoConstFoo> f3 { Create<NoConstFoo>(s, lclId) };
        f3->Print();

        std::unique_ptr<NoConstFoo> f4 { Create<NoConstFoo>(StrWrapper("Rvalue string"), 437) };
        f4->Print();
      }
  }

  void Test_PerfectForwarding()
  {
    std::cout << "######################################## Testing Perfect forwarding ...." << std::endl;
    Problem::TestProblem();
    Solution::TestSolution();
  }
}


