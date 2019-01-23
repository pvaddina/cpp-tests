#include <iostream>
#include <type_traits>

template <typename T1, typename T2>
std::enable_if_t<std::is_same_v<T1,T2> > SameTypeTest()
{
    std::cout << "Both types are the same" << std::endl;
}

template <typename T1, typename T2>
std::enable_if_t<!std::is_same_v<T1,T2> > SameTypeTest()
{
    std::cout << "Both types are not the same" << std::endl;
}

enum EnumTest { one, two, three };
using EnumTestAlias= EnumTest;
struct StructTest {};
class ClassTest {};


void is_same_tests()
{
    SameTypeTest<EnumTest, EnumTestAlias>();
    SameTypeTest<StructTest, EnumTestAlias>();
    SameTypeTest<ClassTest, ClassTest>();
}


