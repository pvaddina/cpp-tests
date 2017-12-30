#include <iostream>

class PrintTest
{
  public:
  virtual void PrintName() = 0;
  virtual void PrintAge() = 0;
};

class P1 : public PrintTest
{
  public:
    virtual void PrintName() { std::cout << "Name: P1" << std::endl; }
    virtual void PrintAge() { std::cout << "Name: P1, Age=X1" << std::endl; }
};

class P2 : public PrintTest
{
  public:
    virtual void PrintName() { std::cout << "Name: P2" << std::endl; }
    virtual void PrintAge() { std::cout << "Name: P2, Age=X2" << std::endl; }
};

template <typename O, typename T>
void Print(O* p, T callbackFn)
{
  (p->*callbackFn)();
}

int main()
{
  P1 p1Obj;
  P2 p2Obj;

  Print(&p1Obj, &PrintTest::PrintName);
  Print(&p1Obj, &PrintTest::PrintAge);
  Print(&p2Obj, &PrintTest::PrintName);
  Print(&p2Obj, &PrintTest::PrintAge);

  return 0;
}
