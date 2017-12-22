#include <iostream>
#include <vector>
#include <string>

void test1()
{
  std::vector<std::string> v {"one", "two", "three", "four", "five", "six", "seven", "ten" };
  std::string in;
  while(true)
  {
    std::cout << "Enter a search string: ";
    std::cin >> in;
    for (const std::string& s : v)
    {
      std::cout << "Current evaluated string:" << s << std::endl;
      if ( s == in )
      {
        std::cout << "String found. Breaking execution.";
        break;
      }
    }
    std::cout << std::endl << std::endl;
  }
}


int main()
{
  test1();

  return 0;
}
