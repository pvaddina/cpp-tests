#include <iostream>
#include <string>

namespace A
{
   namespace B
   {
      void PrintText(std::string str)
      {
         std::cout << str << std::endl;
      }

      void PrintNum(int i)
      {
         std::cout << i << std::endl;
      }

      template <typename Fn, typename T>
      void Print(Fn fn, T val)
      {
         (*fn)(val);
      }

      void TestTypelessArg()
      {
         Print(&PrintText, "This is a string");
         Print(&PrintNum, 345);
      }
   }
}

namespace C
{
   namespace D
   {
      typedef void (*PrintTemp)(const std::string);
      void PrintText(const std::string str) { std::cout << str << "-PrintText" << std::endl; }
      void PrintNum(const std::string str) { std::cout << str << "-PrintNum" << std::endl; }

      template <PrintTemp T>
      class PSim
      {
         public:
            void Print()
            {
               T(std::string("TestString"));
            }
      };

      typedef PSim<&PrintText> PSimOne;
      typedef PSim<&PrintNum> PSimTwo;

      void TestTypedArg()
      {
         PSimOne one;
         PSimTwo two;
         one.Print();
         two.Print();
      }
   }
}

int main()
{
   A::B::TestTypelessArg();
   C::D::TestTypedArg();
   return 0;
}

