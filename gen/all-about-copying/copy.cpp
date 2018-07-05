#include <iostream>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// Constructing an object using default copy and constructor
///////////////////////////////////////////////////////////////////////////
struct Basic
{
  int a;
  double b;
  void Print(const std::string& ip)
  {
    std::cout << ip << ": a=" << a << ", b=" << b << std::endl;
  }
  Basic(const Basic&) = default;
  Basic() = default;
};

void StructIniTest()
{
  std::cout << "######################## In StructIniTest" << std::endl;
  Basic objBasic;
  objBasic.Print("Default Initialization of objBasic");
  
  Basic objBasic0 {23, 545.8787};
  objBasic0.Print("Field initialization with Braces, objBasic0");
  
  Basic objBasic1;
  objBasic1.Print("Default Initialization of objBasic1");
  objBasic1.a = 437;
  objBasic1.b = 437.437;
  objBasic1.Print("Initialize the values individually, objBasic1");
  
  Basic objBasic2;
  objBasic2 = objBasic1;
  objBasic2.Print("Default copying objBasic1 to objBasic2, objBasic2");
  
  Basic objBasic3(objBasic2);
  objBasic3.Print("Default copy constructing objBasic3 from objBasic2, objBasic3");

  Basic objBasic4{objBasic1};
  objBasic4.Print("Default copy constructing objBasic4 from objBasic1 using Brace initialization, objBasic4");

  Basic objBasic5({objBasic1});
  objBasic5.Print("Default Copy constructing objBasic5 from objBasic1 passed as an initializer list, objBasic5");
}

/////////////////////////////////////////////////////////////////////////////
// Constructing an object using user defined constructors
///////////////////////////////////////////////////////////////////////////
struct Adv
{
  int a;
  double b;
  Adv(const Adv& rhs)
  {
    std::cout << "In copy constructor of Adv" << std::endl;
    a = rhs.a;
    b = rhs.b;
  }
  Adv() 
  {
    std::cout << "In default constructor of Adv" << std::endl;
    a = 111;
    b = 222.333;
  }
  void operator=(const Adv& rhs)
  {
    std::cout << "In assignment operator of Adv" << std::endl;
    a = rhs.a;
    b = rhs.b;
  }
  void Print(const std::string& ip)
  {
    std::cout << ip << ": a=" << a << ", b=" << b << std::endl;
  }
}; 

Adv GetNewAdv()
{
  return Adv();
}

void AdvTest()
{
  std::cout << "######################## In AdvTest" << std::endl;
  std::cout << "Test-1: Adv a1 = GetNewAdv()" << std::endl;
  Adv a1 = GetNewAdv();

  std::cout << "\nTest-2: Adv a2(GetNewAdv())" << std::endl;
  Adv a2(GetNewAdv());

  std::cout << "\nTest-3: a3 = GetNewAdv()" << std::endl;
  Adv a3;
  a3 = GetNewAdv();
}

int main()
{
    StructIniTest();
    AdvTest();
    return 0;
}
