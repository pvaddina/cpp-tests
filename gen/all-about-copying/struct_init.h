#include <iostream>
#include <string>
#include "myprint.h"

namespace A
{
  namespace TEST1
  {
    /////////////////////////////////////////////////////////////////////////////
    // Constructing an object using default constructor and copy constructor
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

    void do_test()
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
  }

  namespace TEST2
  {
    struct SegReadAddress
    {
      int segment;
      int deviceAdr;
      int command;
      int *p;
    };

    struct SegWriteAddress : public SegReadAddress
    {
      SegWriteAddress(int a1, int a2, int a3, int* ptr, int a4) : SegReadAddress{a1,a2,a3,ptr}, writeValue(a4) {}
      int writeValue;
    };

    void Print(SegReadAddress& obj)
    {
      std::cout << obj.segment << " " << obj.deviceAdr << " " << obj.command << " *p=" << *(obj.p) << std::endl;
    }

    void Print(SegWriteAddress& obj)
    {
      std::cout << obj.segment << " " << obj.deviceAdr << " " << obj.command << " " << obj.writeValue << " *p=" << *(obj.p) << std::endl;
    }

    void testBase()
    {
      int temp = 437;
      SegReadAddress aOne { 1, 2, 3, &temp };
      //SegReadAddress aTwo { .segment=4, .deviceAdr=5, .command=6 };
      Print(aOne);
      temp = 555;
      Print(aOne);
    }

    void testDerived()
    {
      int temp = 666;
      SegWriteAddress bOne { 7, 8, 9, &temp, 10 };
      SegWriteAddress bTwo(bOne);
      Print(bOne);
      Print(bTwo);
      temp = 777;
      SegWriteAddress bThree = bOne;

      Print(bThree);
    }

    void do_test()
    {
      std::cout << "##################### In do_struct_init_test\n";
      testBase();
      testDerived();
    }
  }


  void StructIniTest()
  {
    utils::Print1("In StrutIniTest");
    TEST1::do_test();
    TEST2::do_test();
  }
}
