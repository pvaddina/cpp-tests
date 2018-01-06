#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <numeric>
#include <condition_variable>
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>

std::mutex m;
std::condition_variable c;
std::mutex pMutex;

const int TEST_FOR_MAX_VAL = 54;

class LockPrint
{
  public:
    template <typename T>
    void Print(T&& p)
    {
      std::lock_guard<std::mutex> lk(pMutex);
      std::cout << p << std::endl;
    }
} LPrint;

template <int MIN, int MAX>
struct RandomGen
{
  RandomGen() { 
    std::srand(std::time(nullptr)); // use current time as seed for random generator
  }
  
  int GetRandom()
  {
    return MIN + (std::rand() % (MAX - MIN + 1) );
  }
};

using RandomGenerator = RandomGen<6, 99>;
RandomGenerator RGen;

class MyThread
{
public:
  void Init()
  {
    std::lock_guard<std::mutex> lk(m);
    
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
    data.push_back(RGen.GetRandom());
  }
    
  void prep()
  {
    while(true)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::lock_guard<std::mutex> lk(m);
      std::srand(std::time(nullptr)); // use current time as seed for random generator
      const int r = RGen.GetRandom();
      data.push_back(r);

      std::stringstream s;
      s << "Adding " << r << " to the vector\n";
      LPrint.Print(s.str());

      c.notify_one();
    }
  }

  void summer()
  {
    while(true)
    {
      std::unique_lock<std::mutex> lk(m);
      c.wait(lk, [this](){ return !data.empty(); });
      if (!data.empty())
      {
        std::for_each(data.begin(), data.end(), [](const int& v) {
            std::stringstream s;
            if ( v > TEST_FOR_MAX_VAL )
            {
              s << "Found " << v << " in the vector, which is greater than MAX\n";
            }
            else
            {
              s << "Found " << v << " in the vector";
            }
            LPrint.Print(s.str());
            });
        data.clear();
      }
    }
  }

private:
  std::vector<int> data;  
};

int main()
{
  MyThread t;
  t.Init();

  std::thread prep(&MyThread::prep, t);
  std::thread summer(&MyThread::summer, t);

  prep.join();
  summer.join();

  return 0;
}


