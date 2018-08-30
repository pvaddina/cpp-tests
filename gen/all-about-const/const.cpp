#include <iostream>
#include "gen_tests.h"
#include "const_objs.h"
#include "strprint.h"


int main()
{
  PUtils::PrintHeader1("A::do_const_obj_tests()");
  A::do_const_obj_tests();

  utils::PrintHeader1("B::do_gen_tests()");
  B::do_gen_tests();
    
  return 0;
}
