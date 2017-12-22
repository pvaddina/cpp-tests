#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


void test_find()
{
  std::vector<std::string> s{ "One", "Two", "Three", "Four", "Five", "Ten" };
  std::string in;

  while (true)
  {
    std::cout << "Enter the search string: ";
    std::cin >> in;

    auto v = std::find(s.begin(), s.end(), in);

    if (v == std::end(s))
    {
      std::cout << "Found nothing ...." << std::endl;
    }
    else
    {
      std::cout << "Found this in the vector:" << *v << std::endl;
    }
    std::cout << std::endl << std::endl;
  }
}

int main()
{
  test_find();

  return 0;
}

