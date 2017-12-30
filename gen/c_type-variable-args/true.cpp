#include <iostream>


    struct TrueCompare
    {
      bool operator()(...) const { return true; }
    };


int main()
{
  TrueCompare one, two, three, four;
  std::cout << one(23) << std::endl;
  std::cout << one(23.34) << std::endl;
  std::cout << one(two, 3, 6, 9232, 343.5435, "tesxt") << std::endl;
  std::cout << one("some>Tem") << std::endl;

  return 0;
}

