#include <iostream>
using namespace std;


void PrintText(std::string str)
{
  std::cout << str << endl;
}

void PrintNum(int i)
{
  std::cout << i << endl;
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

