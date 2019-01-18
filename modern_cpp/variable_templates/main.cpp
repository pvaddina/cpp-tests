#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <memory>
#include <array>
#include <functional>


template <typename T>
T myContainer{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

auto print = [](auto& container, auto&& str) -> void {
  std::cout << str;
  for (auto& i : container) std::cout << i << " ";
  std::cout << std::endl;
};

void InitContainers()
{
  auto vecContainer = myContainer<std::vector<int> >;
  print(vecContainer, "Vector: ");

  auto listContainer = myContainer<std::list<int> >;
  print(listContainer, "List: ");

  // Error !!    
  //auto strContainer = myContainer<std::vector<std::string> >;
}



int main()
{
  InitContainers();

  return 0;
}

