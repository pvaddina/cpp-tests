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

  Basic objBasic6 { 55, 55.66 };
  objBasic6.Print("Default initialization of objBasic6");
  objBasic6 = objBasic5;
  objBasic6.Print("Default assignment of objBasic6");
}

