#include <iostream>
using namespace std;

template <unsigned long N>
struct binary
{
  static unsigned const value = binary<N/10>::value << 1 // prepend higher bits
                                                          | N%10; // to lowest bit
};

template <> struct binary<0>
{
  static unsigned const value = 0;
};

int main()
{
  cout << binary<11000>::value << endl;
  return 0;
}
