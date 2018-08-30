#include <iostream>
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"

struct impl
  : public one
  , public two
  , public three
  , public four 
{
  virtual void one_1() { std::cout << "In function one_1" << std::endl; }
  virtual void one_2()  { std::cout << "In function one_2" << std::endl; }
  virtual void one_3()  { std::cout << "In function one_3" << std::endl; }
  virtual void two_1() { std::cout << "In function two_1" << std::endl; } 
  virtual void two_2()  { std::cout << "In function two_2" << std::endl; }
  virtual void two_3() { std::cout << "In function two_3" << std::endl; } 
  virtual void three_1() { std::cout << "In function three_1" << std::endl; } 
  virtual void three_2() { std::cout << "In function three_2" << std::endl; } 
  virtual void three_3()  { std::cout << "In function three_3" << std::endl; }
  virtual void four_1() { std::cout << "In function four_1" << std::endl; } 
  virtual void four_2()  { std::cout << "In function four_2" << std::endl; }
  virtual void four_3()  { std::cout << "In function four_3" << std::endl; }
};

