#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

std::vector<int> data = {34, 3421, 675, 1143, 9856, 112, 652, 123, 99583 };
const int COMPARE_VAL = 112;

/////////////////////////////////////////////////////////////////////
//
// Function definitions
// 
/////////////////////////////////////////////////////////////////////
/*
template< class InputIt, class UnaryPredicate >
InputIt find_if( InputIt first, InputIt last, UnaryPredicate p );

template< class InputIt, class UnaryPredicate >
constexpr InputIt find_if( InputIt first, InputIt last, UnaryPredicate p );

template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
ForwardIt find_if( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );
*/

struct Comparer
{
  Comparer(const int v) : val(v) {}
  int val;
  void Print(std::string s) const { std::cout << s << ":" << val << std::endl; }
  bool operator()(const int i)
  {
    std::cout << "Comparing val=" << val << ", against i=" << i << std::endl;
    if (i==val)
    {
      val *= 2;
      return true;
    }
    return false;
  }

  // Note: Enabling the following lines will result in compilation
  // errors in Test1(), since the predicates are always passed by value
  // (Check the definitions above)
  // Comparer(const Comparer&) = delete;
  // Comparer& operator=(const Comparer&) = delete;
};

void Test1()
{
  std::cout << std::endl << "Test-1:Demonstrate that the callable is passed by value and not by reference" << std::endl;

  const Comparer comp(COMPARE_VAL);
  comp.Print("Value before the find operation");

  // Note when the functor 'comp' is passed in the following line, it will be
  // passed by value and not by reference
  auto it = std::find_if(std::begin(data), std::end(data), comp);
  if (it != std::end(data))
  {
    comp.Print("Value after the find operation (Note that it is still the same)");
  }
}

void Test2()
{
  std::cout << std::endl << "Test-2:Demonstrate passing the callable as reference and not by value" << std::endl;

  const Comparer comp(COMPARE_VAL);
  comp.Print("Value before the find operation");

  //auto it = std::find_if(std::begin(data), std::end(data), std::ref(comp));
  auto it = std::find_if(std::begin(data), std::end(data), comp);
  if (it != std::end(data))
  {
    comp.Print("Value after the find operation (Note that it is still the same)");
  }
}

bool HardcodedComparer(const int i)
{
  std::cout << "Comparing against i=" << i << std::endl;
  return i == COMPARE_VAL;
}

void Test3()
{
  std::cout << std::endl << "Test-3:Demonstrate using a free function" << std::endl;

  std::function<bool(const int)> f = {HardcodedComparer};
  auto it = std::find_if(std::begin(data), std::end(data), f);
  if (it != std::end(data))
  {
    std::cout << "Found the value=" << *it << std::endl;
  }
}

void Test4()
{
  std::cout << std::endl << "Test-4:Demonstrate using a Lambda function" << std::endl;

  const int valToFind = COMPARE_VAL;
  auto it = std::find_if(std::begin(data), std::end(data), [valToFind](const int i) -> bool { return i==COMPARE_VAL; });
  if (it != std::end(data))
  {
    std::cout << "Found the value=" << *it << std::endl;
  }
}

int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
}

