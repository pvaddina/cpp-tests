#include <iostream>
#include "gen_tests.h"
#include "const_objs.h"


int main()
{
  std::cout << "A::do_const_obj_tests()";
  A::do_const_obj_tests();

  std::cout << "B::do_gen_tests()";
  B::do_gen_tests();
    
  return 0;
}
