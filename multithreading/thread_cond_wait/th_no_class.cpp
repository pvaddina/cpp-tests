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
#include <ctime>

std::mutex m;
std::condition_variable c;
std::mutex pMutex;

const int THREAD_SLEEP_TIME = 1000;
const int TEST_FOR_MAX_VAL = 437;
const int RAND_GEN_MIN = 0;
const int RAND_GEN_MAX = 1000;


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

using RandomGenerator = RandomGen<RAND_GEN_MIN, RAND_GEN_MAX>;
RandomGenerator RGen;

  std::vector<int> data;  

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
      std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME ));
      std::lock_guard<std::mutex> lk(m);
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
      c.wait(lk, [](){ return !data.empty(); });
      if (!data.empty())
      {
        std::for_each(data.begin(), data.end(), [](const int& v) {
            std::stringstream s;
            if ( v > TEST_FOR_MAX_VAL )
            {
              s << "\t\t\t\t\t\tFound " << v << " in the vector, which is greater than MAX\n";
            }
            else
            {
              s << "\t\t\t\t\t\tFound " << v << " in the vector";
            }
            LPrint.Print(s.str());
            });
        data.clear();
      }
    }
  }


int main()
{
  Init();

  std::thread p(prep);
  std::thread s(summer);

  p.join();
  s.join();

  return 0;
}



