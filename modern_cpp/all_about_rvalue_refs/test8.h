#include <memory>
#include <string>
#include <iostream>
#include <tuple>

namespace Test8
{ 
  using BoxDesc = std::tuple<int, std::string>;
  using BoxDescRvalue = std::tuple<int, std::string&&>;

  struct Box
  {
    Box(BoxDesc&& inBD)
    {
      std::tie(id, name) = std::move(inBD);
    }

    Box(BoxDescRvalue&& inBD)
    {
      std::tie(id, name) = std::move(inBD);
    }

    void Print() { std::cout << "Box id=" << id << ", name=" << name << std::endl; }

    private:    
    int id = 999;
    std::string name = "some name";
  };


  void Test1()
  {
    std::cout << "In Test-1" << std::endl;
    Box b { BoxDesc(437, "This is 437") };
    b.Print();
  }

  void Test2()
  {
    std::cout << "\n\nIn Test-2" << std::endl;

    std::string name { "This is 3232" };    
    Box b { BoxDesc(3232, name) };
    b.Print();    
    std::cout << "name after moving the tuple=" << name << std::endl; // There should be no change in the string

    Box b1 { BoxDescRvalue(3232, std::move(name)) };
    b1.Print();    
    std::cout << "name after moving=" << name << std::endl; // Since the string has been moved, this will result in an empty name
  }

  void Test()
  {
    Test1();
    Test2();
  }
}
