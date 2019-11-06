#include <iostream>
#include <string>
#include <vector>
#include <tuple>

namespace T1
{
  using MyTyp = std::tuple<std::string, std::vector<int>, std::vector<int>&>;

  void print_vec(const std::vector<int>& v)
  {
    for (auto& it : v)
      std::cout << it << " ";
    std::cout << std::endl;
  }

  void print_mytyp(const std::string&& s, const MyTyp& v)
  {
    std::cout << s << std::endl;
    std::cout << std::get<0>(v) << std::endl;
    print_vec(std::get<1>(v));
    print_vec(std::get<2>(v));
  }

  int Test()
  {
    std::cout << "##################### Test-1: Demonstrate effect of move on referenced values in a tuple" << std::endl;

    std::vector<int> v { 1, 2, 3, 4, 5 };
    std::cout << "\nPrint the vector before any move operation: ";
    print_vec(v);
    MyTyp typ { "Simple String", {9,8,7,6}, std::ref(v) };
    print_mytyp("\nPrinting the tuple right after creation", typ);

    MyTyp typ2 = std::move(typ);
    print_mytyp("\ntyp2=move(typ): Printing 'typ' after the move (Notice 'v' is still valid, as passed by reference')", typ);
    print_mytyp("\ntyp2=move(typ): Printing 'typ2' after the move (Notice 'v' is still valid, as passed by reference')", typ2);

    std::cout << "\nPrint the vector after all the move operations(should remain unchanged as passed by reference only): ";
    print_vec(v);

    std::cout << "\nChanging v[2]=437, and notice the tuples\n";
    v[2] = 437;
    print_vec(v);
    print_mytyp("\nValue of 'typ' after move and value change", typ);
    print_mytyp("\nValue of 'typ2' after move and value change", typ2);

    return 0;
  }
}

int main()
{
  T1::Test();
  return 0;
}
