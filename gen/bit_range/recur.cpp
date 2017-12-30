#include <iostream>

/**
* A simple template implementation to generate the MAX value given the number of bits ... 
* Example:
* 0 bits ==> 0
* 1 bits ==> 1
* 2 bits ==> 3
* 10 bits ==> 1023
*/
template <int NUMBITS> struct BIT_CONST 
{ 
  static const int numbits = NUMBITS; 
  static const int max = (1 << (NUMBITS-1)) | BIT_CONST<NUMBITS-1>::max; 
  static const int mod = max + 1;
};

template <> struct BIT_CONST<0>
{ 
  static const int numbits = 0;
  static const int max = 0;
  static const int mod = 0;
};

typedef BIT_CONST<10> RANGE_TEN_BITS;
typedef BIT_CONST<13> RANGE_THIRTEEN_BITS;
typedef BIT_CONST<10> HRANGE_TEN_BITS;
typedef BIT_CONST<11> SRANGE_TEN_BITS;


int main()
{
  std::cout << BIT_CONST<0>::numbits << " bits ==> " << BIT_CONST<0>::max << std::endl;
  std::cout << BIT_CONST<1>::numbits << " bits ==> " << BIT_CONST<1>::max << std::endl;
  std::cout << BIT_CONST<2>::numbits << " bits ==> " << BIT_CONST<2>::max << std::endl;
  std::cout << BIT_CONST<3>::numbits << " bits ==> " << BIT_CONST<3>::max << std::endl;
  std::cout << BIT_CONST<4>::numbits << " bits ==> " << BIT_CONST<4>::max << std::endl;
  std::cout << BIT_CONST<5>::numbits << " bits ==> " << BIT_CONST<5>::max << std::endl;
  std::cout << BIT_CONST<6>::numbits << " bits ==> " << BIT_CONST<6>::max << std::endl;
  std::cout << BIT_CONST<7>::numbits << " bits ==> " << BIT_CONST<7>::max << std::endl;

  std::cout << RANGE_TEN_BITS::numbits << " bits ==> " << RANGE_TEN_BITS::max << ", mod:" << RANGE_TEN_BITS::mod << std::endl;
  std::cout << RANGE_THIRTEEN_BITS::numbits << " bits ==> " << RANGE_THIRTEEN_BITS::max << ", mod:" << RANGE_THIRTEEN_BITS::mod  << std::endl;
  std::cout << HRANGE_TEN_BITS::numbits << " bits ==> " << HRANGE_TEN_BITS::max  << ", mod:" << HRANGE_TEN_BITS::mod << std::endl;
  std::cout << SRANGE_TEN_BITS::numbits << " bits ==> " << SRANGE_TEN_BITS::max  << ", mod:" << SRANGE_TEN_BITS::mod << std::endl;
  return 0;
}


