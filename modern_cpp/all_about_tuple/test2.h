#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

namespace T4
{
  using IdTyp = std::tuple<std::string, int, int>;
  
  void PrintTuple(IdTyp& t)
  {
      std::cout << std::get<0>(t) << " is " << std::get<1>(t) << " years old. His voter ID is " << std::get<2>(t) << std::endl;
  }      
  
  void Test()
  {
    std::cout << "##################### Test-4: Demonstrate setting individual values of a tuple\n";
    IdTyp t {"Tom", 34, 42356345};
    PrintTuple(t);
    
    auto& name = std::get<0>(t);
    name = "Jim";
    PrintTuple(t);
  }
}

namespace T5
{
  using IdTyp = std::tuple<std::string, int, int>;
  
  void PrintTuple(IdTyp& t)
  {
      std::cout << std::get<0>(t) << " is " << std::get<1>(t) << " years old. His voter ID is " << std::get<2>(t) << std::endl;
  }      
  
  void Test()
  {
    std::cout << "##################### Test-5: Demonstrate structured bindings\n";
    IdTyp t {"Tom", 34, 42356345};
    PrintTuple(t);
    
    auto& [name, age, id] = t;
    name = "Jim";
    age = 49;
    id = 87419883;
    PrintTuple(t);
  }
}


namespace T6
{
  using TNameAge = std::tuple<std::string&&, int&&>;
  using TNameAgeCountry = std::tuple<std::string&&, int&&, std::string&&>;
  
  void PrintTuple(TNameAge&& t)
  {
      std::cout << "In PrintTuple(TNameAge&& t)" << std::endl;
      auto&& [name, age] = std::move(t);
      std::cout << name << " is " << age << " years old." << std::endl;
      
      const auto& [rname, rage] = std::move(t);
      std::cout << rname << " is " << rage << " years old." << std::endl;

      auto [nname, nage] = std::move(t);
      std::cout << nname << " is " << nage << " years old." << std::endl;
  }
  
  void PrintTuple(TNameAgeCountry&& t)
  {
      std::cout << "In PrintTuple(TNameAgeCountry&& t)" << std::endl;
      const auto& [name, age, country] = std::move(t);
      std::cout << name << " is " << age << " years old and lives in " << country << std::endl;
  }
  
  void Test()
  {
    std::cout << "##################### Test-6: Demonstrate usage of std::forward_as_tuple\n";
    PrintTuple(std::forward_as_tuple(std::string("Tom"), 23));
    PrintTuple(std::forward_as_tuple(std::string("Jim"), 85, std::string("Russia")));
    PrintTuple(std::forward_as_tuple("Jim", 85, "Russia"));
  }
}


