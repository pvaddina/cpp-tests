#include <iostream>

struct UeSchedulerBase
{
    void DoSomething() { std::cout << "Do something common" << std::endl; DoSpecific(); }
    void DoSpecific() { std::cout << "Nothing specific" << std::endl; }
};

struct NoUeScheduler : public UeSchedulerBase
{
    void DoSpecific() { std::cout << "Specefic to NoUeScheduler" << std::endl; }
};

struct ConnUeScheduler : public UeSchedulerBase
{
    void DoSpecific() { std::cout << "Specefic to ConnUeScheduler" << std::endl; }
};

int main()
{
  NoUeScheduler noUe;
  ConnUeScheduler connUe;

  noUe.DoSomething();
  connUe.DoSomething();

  return 0;
}

