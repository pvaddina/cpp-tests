#include <iostream>
#include <string>
#include "myprint.h"
#include "struct_init.h"
#include "copy_elision.h"

int main()
{
  utils::PrintHeader1("A::StructIniTest()");
  A::StructIniTest();

  utils::PrintHeader1("B::CopyElisionTest()");
  B::CopyElisionTest();
  return 0;
}
