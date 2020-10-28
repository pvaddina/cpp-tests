#include <iostream>
#include <string>


namespace B
{
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

  void CopyElisionTest()
  {
    std::cout << "############################## In CopyElisionTest\n";
    std::cout << "Test-1: Adv a1 = GetNewAdv()\n";
    Adv a1 = GetNewAdv();

    std::cout << "\nTest-2: Adv a2(GetNewAdv())\n";
    Adv a2(GetNewAdv());

    std::cout << "\nTest-3: a3 = GetNewAdv()\n";
    Adv a3;
    a3 = GetNewAdv();

    std::cout << "\nTest-4: Adv a4 = Adv(Adv(Adv())). According to the spec this statement should lead to a call to the default constructor only. There **should** be no call to the copy or move constructor of 'Adv'. But not all compilers abide by it.\n";
    Adv a4 = Adv(Adv(Adv()));
  }

}
