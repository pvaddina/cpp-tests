#include <iostream>

template <typename... Ts>
size_t GetCount(Ts... ts)
{ 
  return sizeof...(ts);
};

int main()
{
  std::cout << "Number of arguments: " << GetCount(2, 43.567, 2, 32, 5656) << std::endl;
}



