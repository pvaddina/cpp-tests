/**
 * A simple example showing how the different guard functions work
 * - lock_guard
 * - unique_lock
 */



#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex m;

class LGDemo
{
  public:
    LGDemo(const int time, const std::string s) 
      : mSleepUnits(time), mPrintStr(s) {}

    void Worker()
    {
      std::chrono::milliseconds t(mSleepUnits); // Sleep time
      while(true) 
      {
        std::this_thread::sleep_for(t);
        std::lock_guard<std::mutex> mTex(m);
        std::cout << mPrintStr << std::endl;
      }
    }

  private:
    const int mSleepUnits; // Number of sleep units (without any real time units)
    const std::string mPrintStr; // A print string
};


int main()
{
  LGDemo firstThread(100,  "-------------- Thread-1 ------------------");
  LGDemo secondThread(500, "                                            ++++++++++++++ Thread-2 ++++++++++++++++++");

  std::thread t1(&LGDemo::Worker, std::ref(firstThread));
  std::thread t2(&LGDemo::Worker, std::ref(secondThread));

  t1.join();
  t2.join();

  return 0;
}


