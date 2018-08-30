#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

struct A
{
  int v1;
  std::string v2;
  A(int _v1, std::string&& _v2) : v1(_v1), v2(_v2) {}
  A(const A& a)   // Note this will not work without the copy contructor
  { 
    std::cout << "In copy constructor of A" << std::endl; 
    v1 = a.v1;
    v2 = a.v2;
  }
  void Print() const { std::cout << "V1=" << v1 << ", V2=" << v2 << std::endl; }
};

struct B
{
  int v1;
  std::string v2;
  B(int _v1, std::string&& _v2) : v1(_v1), v2(_v2) {}
  B(const B& b)  // Note this will not work without the copy contructor
  { 
    std::cout << "In copy constructor of B" << std::endl; 
    v1 = b.v1;
    v2 = b.v2;
  }
  void Print() const { std::cout << "V1=" << v1 << ", V2=" << v2 << std::endl; }
};

struct C
{
  int v1;
  std::string v2;
  C(int _v1, std::string&& _v2) : v1(_v1), v2(_v2) {}
  C(const C& c) = delete; // Note the copy constructor is deleted
  void Print() const { std::cout << "V1=" << v1 << ", V2=" << v2 << std::endl; }
};

struct Foo 
{
  std::vector<int> mem = {1,2,3}; // list-initialization of a non-static member
  std::vector<int> mem2;
  Foo() : mem2{-1, -2, -3} {} // list-initialization of a member in constructor
  Foo(std::initializer_list<int> v1, std::initializer_list<int> v2) : mem(v1), mem2(v2) {}
  void Print()
  {
    std::cout << "Printing Foo::mem: ";
    for (auto it : mem)
      std::cout << it << " ";
    std::cout << std::endl;

    std::cout << "Printing Foo::mem2: ";
    for (auto it : mem2)
      std::cout << it << " ";
    std::cout << std::endl << std::endl << std::endl;
  }    
};

struct Foo2
{
  std::vector<A> mem;
  Foo2(std::initializer_list<A> v1) : mem(v1) {}
  void Print()
  {
    std::cout << "Printing Foo2::mem: ";
    for (auto& it : mem)
    {
      it.Print();
    }
    std::cout << std::endl;
  }
};

struct Foo3
{
  const A in;
  B out;
  C& temp;
  Foo3(const A& a, B&& b, C& c) : in(a), out(b), temp(c) {} // Because of the way the constructor arguments are defined 'C' 
                                                            // is allowed to have no copy constructor, whereas the other have to have one.
  // Foo3 f1 { {123, "In String"}, { 567, "Out string" }, *c }; // Does not work for the constructor definition: 
                                                                // Foo3(const A& a, B& b, C& c) : in(a), out(b), temp(c) {}

  void Print() const {in.Print(); out.Print(); temp.Print(); }
};
  


void testFoo()
{
  std::cout << "############## TestFoo ##############" << std::endl;
  Foo f1;
  f1.Print();
  
  Foo f2{ {22,33,44,55,66,77,88,99}, {-22,-33,-44,-55,-66,-77,-88,-99} };
  f2.Print();
}

void testFoo2()
{
  std::cout << std::endl << std::endl << "############## TestFoo2 ##############" << std::endl;
  Foo2 f1{ {111,std::move("Str1")}, {222,std::move("Str2")}, {333, std::move("Str3")} };
  f1.Print();
}

void testFoo3()
{
  std::cout << std::endl << std::endl << "############## TestFoo3 ##############" << std::endl;
  C *c = new C{445566, "String on the heap"};
  Foo3 f1 { {123, "In String"}, { 567, "Out string" }, *c };
  f1.Print();
  //f1.in.v2 = "Cannot do this. Will result in an ERROR";
  c->v2 = "String on the heap is now replaced with this temporary string";
  f1.out.v2 = "This is OK.";
  f1.Print();
}

int main()
{
  testFoo();
  testFoo2();
  testFoo3();
  
  return 0;
}

