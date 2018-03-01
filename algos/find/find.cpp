#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> data = {34, 3421, 675, 1143, 9856, 112, 652, 123, 99583 };
const int COMPARE_VAL = 112;


/////////////////////////////////////////////////////////////////////
//
// Function definitions
// 
/////////////////////////////////////////////////////////////////////
/*
template< class InputIt, class T >
InputIt find( InputIt first, InputIt last, const T& value );

template< class InputIt, class T >
constexpr InputIt find( InputIt first, InputIt last, const T& value );

template< class ExecutionPolicy, class ForwardIt, class T >
ForwardIt find( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value );
*/

/////////////////////////////////////////////////////////////////////
//
// TEST-1
// 
/////////////////////////////////////////////////////////////////////
namespace FT1
{
  struct Result
  {
    Result(const int v) : val(v) {}
    int val;
    void Print(std::string s) { std::cout << s << ":" << val << std::endl; }

    // No copy and assignment operators
    Result(const Result&) = delete;
    Result& operator=(const Result&) = delete;
  };

  struct Comparer
  {
    Comparer(Result& r) : mRes(r) {}
    Result& mRes;

    // No copy and assignment operators
    Comparer(const Comparer&) = delete;
    Comparer& operator=(const Comparer&) = delete;
  };

  bool operator==(const int i, const Comparer& c)
  {
    std::cout << "Comparing against:" << i << std::endl;
    if (i==c.mRes.val)
    {
      c.mRes.val *= 2;
      return true;
    }
    else
    {
      return false;
    }
  }

  void Test()
  {
    std::cout << "Test-1:Use the functor for Comparison and also to do other operations that survive past the algorithm operation" << std::endl;
    Result res(COMPARE_VAL);
    res.Print("Value before the find operation");
    const Comparer comp(res);
    auto it = std::find(std::begin(data), std::end(data), comp);
    if (it != std::end(data))
    {
      res.Print("Value after the find operation (multiplied by 2)");
    }
  }
}

/////////////////////////////////////////////////////////////////////
//
// TEST-2
// 
/////////////////////////////////////////////////////////////////////
namespace FT2
{
  struct Comparer
  {
    Comparer(const int v) : val(v) {}
    int val;
    void Print(std::string s) const { std::cout << s << ":" << val << std::endl; }

    // No copy and assignment operators
    Comparer(const Comparer&) = delete;
    Comparer& operator=(const Comparer&) = delete;
  };

  bool operator==(const int i, const Comparer& c)
  {
    std::cout << "Comparing against:" << i << std::endl;
    if (i==c.val)
    {
      // c.val *= 2;  // FAILS. 'c' is const
      return true;
    }
    else
    {
      return false;
    }
  }

  void Test()
  {
    std::cout << std::endl << "Test-2:Use the functor for normal comparison oerations. Note that no other information can be saved" << std::endl;
    const Comparer comp(COMPARE_VAL);
    comp.Print("Value before the find operation");
    auto it = std::find(std::begin(data), std::end(data), comp);
    if (it != std::end(data))
    {
      comp.Print("Value after the find operation (Obviously same as earlier)");
    }
  }
}

/////////////////////////////////////////////////////////////////////
//
// TEST-3
// 
/////////////////////////////////////////////////////////////////////
namespace Normal
{
  void Test()
  {
    std::cout << std::endl << "Test-3: Simple case of comparing without any Functors" << std::endl;
    auto it = std::find(std::begin(data), std::end(data), COMPARE_VAL);
    if (it != std::end(data))
    {
      std::cout << *it << std::endl;
    }
  }
}




int main()
{
  FT1::Test();
  FT2::Test();
  Normal::Test();
}
