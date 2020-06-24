#include <iostream>
#include <string>
#include <vector>
#include <memory>


namespace T1
{
  void Check(std::weak_ptr<void> p)
  {
    if (p.expired())
      std::cout << "p is not valid\n" ;
    else
      std::cout << "p is still valid\n" ;
  }

  struct CheckPtr
  {    
    CheckPtr() {}
    void Set(std::weak_ptr<void> p) { mP = p; }
    void Valid()
    {
      if (mP.expired())
        std::cout << "p is not valid\n" ;
      else
        std::cout << "p is still valid\n" ;
    }
    std::weak_ptr<void> mP;
  };


  void TestWP()
  {
    {
      std::shared_ptr<int> p { new int };
      *p = 437;
      Check(p);
      p.reset();
      Check(p);
    }

    {
      std::cout << "====================================================\n";
      std::shared_ptr<std::string> p { new std::string };
      *p = "Test string";
      CheckPtr cptr;
      cptr.Set(p);

      Check(p);
      cptr.Valid();

      p.reset();
      Check(p);
      cptr.Valid();
    }

    {
      std::cout << "====================================================\n";
      CheckPtr cptr;
      {
        std::shared_ptr<std::string> p { new std::string };
        *p = "Test string";
        cptr.Set(p);

        Check(p);
        cptr.Valid();
      }
      cptr.Valid();
    }
  }
}




