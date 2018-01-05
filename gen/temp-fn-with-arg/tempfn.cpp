#include <iostream>
#include <string>

void PrintText(std::string str)
{
  std::cout << str << std::endl;
}

void PrintNum(int i)
{
  std::cout << i << std::endl;
}


template <typename Fn, typename T>
void Print(Fn fn, T val)
{
  (*fn)(val);
}

int main()
{
  Print(&PrintText, "This is a string");
  Print(&PrintNum, 345);

  return 0;
}

