#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex m;


// A traits class definition accepting either a std::lock_guard/std::unique_lock.
// It implements a single generic function which controls if the extra call to the
// lock() method is present or not, depending on the type of the lock handler.
template <typename T>
struct LockTraits
{
    static void do_lock(T& t) {}
};

template <>
struct LockTraits<std::unique_lock<std::mutex> >
{
    static void do_lock(std::unique_lock<std::mutex>& t)
    {
      t.lock();
    }
};


template<typename MTYPE>
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
        MTYPE mTex(m);
        LockTraits<MTYPE>::do_lock(mTex);
        std::cout << mPrintStr << std::endl;
      }
    }

  private:
    const int mSleepUnits; // Number of sleep units (without any real time units)
    const std::string mPrintStr; // A print string
};


int main()
{
  using LockGuardTester = LGDemo<std::lock_guard<std::mutex> >;
  using UniqueLockTester = LGDemo<std::unique_lock<std::mutex> >;
  LockGuardTester firstThread(100,  "-------------- Thread-1 ------------------");
  LockGuardTester secondThread(500, "                                            ++++++++++++++ Thread-2 ++++++++++++++++++");

  std::thread t1(&LockGuardTester::Worker, std::ref(firstThread));
  std::thread t2(&LockGuardTester::Worker, std::ref(secondThread));

  t1.join();
  t2.join();

  return 0;
}


