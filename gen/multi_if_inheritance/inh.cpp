#include <iostream>

class Inf
{
   public:
      virtual void Print() = 0;
};

class AInf : public Inf
{
   public:
      virtual void APrint() = 0;
};

class BInf : public Inf
{
   public:
      virtual void BPrint() = 0;
};

class Impl : public AInf, public BInf
{
   public:
      void Print()
      {
         std::cout << "Generic Print" << std::endl;
      }
      void APrint()
      {
         std::cout << "A Specific Print" << std::endl;
      }
      void BPrint()
      {
         std::cout << "B Specific Print" << std::endl;
      }
};

void PrintA(AInf* p)
{
   p->Print();
   p->APrint();
}

void PrintB(BInf* p)
{
   p->Print();
   p->BPrint();
}


int main()
{
   Impl i;

   PrintA(&i);
   PrintB(&i);

   return 0;
}



