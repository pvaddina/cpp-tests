#include <iostream>
#include <chrono>
#include <thread>


void foo()
{
  auto i = 0;
  while ( i < 10000)
  {
     std::cout << "Current count:" << i << std::endl;
     std::chrono::milliseconds waitTime(1);
     std::this_thread::sleep_for( waitTime);
     ++i;
  }
}

int main()
{
  std::thread t( foo );

  t.join();

  std::cout << "About to exit ... " << std::endl;

  return 0;
}
