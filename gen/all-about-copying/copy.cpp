#include <iostream>
#include <string>
#include "struct_init.h"
#include "copy_elision.h"

int main()
{
  A::StructIniTest();
  B::CopyElisionTest();

  return 0;
}
