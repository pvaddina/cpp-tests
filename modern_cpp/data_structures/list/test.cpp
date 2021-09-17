#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename T>
void Print(const std::string&& s, const std::list<T>& l)
{
  std::cout << s ;
  for (const auto& it: l)
    std::cout << it << " "; 
  std::cout << std::endl;
}

namespace T1
{
  void ConcatTests()
  {
    std::list<int> l1 {1, 2, 3, 4, 5};
    std::list<int> l2 {11,22,33,44,55};
    Print("l1 = ", l1);
    Print("l2 = ", l2);
    
    // l3 = l1 + l2
    std::list<int> l3 = l1;
    std::copy(l2.begin(), l2.end(), std::back_inserter(l3));
    Print("l3 = ", l3);

    // l4 = l2 + l1
    std::list<int> l4 = l1;
    std::copy(l2.begin(), l2.end(), std::front_inserter(l4));
    Print("l4 = ", l4);

    // l5 = l2 + l1
    std::list<int> l5 = l1;
    std::copy(l2.rbegin(), l2.rend(), std::front_inserter(l5));
    Print("l5 = ", l5);

    // l6 = l2 + l1
    std::list<int> l6;
    std::copy(l1.begin(), l1.end(), std::back_inserter(l6));
    std::copy(l2.rbegin(), l2.rend(), std::front_inserter(l6));
    Print("l6 = ", l6);
  }
}

    

int main()
{
    T1::ConcatTests();    
    return 0;
}

