#include <iostream>
#include <string>
#include "struct_init.h"
#include "copy_elision.h"
#include "copyconstructor_inheritence.h"


int main()
{
  A::StructIniTest();
  B::CopyElisionTest();
  C::TestCopyConstructorWithInheritence();

  return 0;
}
