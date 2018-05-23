#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex m;


// A traits class definition accepting either a std::lock_guard<std::mutex>/std::unique_lock<std::mutex>.
// It implements simple generic functionis to allow different combination of behavior that are possible
// by combining the types with the DEFER flag
//
//
// Trait-1: Used for std::lock_guard<std::mutex> aswell as std::unique_lock<std::mutex>. 
// The defer flag does not play a role here. In case of std::lock_guard, it is anyway not used.
// Where as std::unique_lock can also be used as an std::lock_guard, when deferring is not used
template <typename T, bool DEFER>
struct LockTraits
{
  static T GetNewLock(std::mutex& _m) { return T(_m); } 
  static void LockIt(T& _t) { /* Do Nothing. Mutex is already locked.*/ }
};

// Trait-2: Used when the types and the DEFER flag are as below in the definition
// This is the case specific to std::unique_lock and when deferring is allowed
template <>
struct LockTraits<std::unique_lock<std::mutex>, true >
{
  static std::unique_lock<std::mutex> GetNewLock(std::mutex& _m) { return std::unique_lock<std::mutex>(_m, std::defer_lock); }
  static void LockIt(std::unique_lock<std::mutex>& t)  { t.lock(); /* Mutex is locked only after this step */}
};


/**
 * A simple class defining a function which will act as the thread body
 * MTYPE --> The type of the lock defined
 * LTYPE --> True when deferring is allowed, and false, when otherwise or not applicable
 * */ 
template<typename MTYPE, bool LTYPE>
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
        MTYPE mTex = LockTraits<MTYPE,LTYPE>::GetNewLock(m);
        LockTraits<MTYPE,LTYPE>::LockIt(std::ref(mTex));
        std::cout << mPrintStr << std::endl;
      }
    }

  private:
    const int mSleepUnits; // Number of sleep units (without any real time units)
    const std::string mPrintStr; // A print string
};

// Type definition when the thread operates with std::lock_guard
using LockGuardTester = LGDemo<std::lock_guard<std::mutex>, false >;
// Type definition when the thread operates with std::unique_lock, and when no deferring is used
using NonDeferringUniqueLock = LGDemo<std::unique_lock<std::mutex>, false>;
// Type definition when the thread operates with std::unique_lock and deferring the lock to a later point
using DeferringUniqueLock = LGDemo<std::unique_lock<std::mutex>, true>;


// A simple test body defining two threads with different sleep times.
// The behavior should be the same for any type of lock combination as defined above
template <typename T>
void Test()
{
  T firstThread(100,  "-------------- Thread-1 ------------------");
  T secondThread(500, "                                            ++++++++++++++ Thread-2 ++++++++++++++++++");

  std::thread t1(&T::Worker, std::ref(firstThread));
  std::thread t2(&T::Worker, std::ref(secondThread));

  t1.join();
  t2.join();
}

#define UNIQUE_LOCK_WITH_DEFERRING

int main()
{
#if defined(LOCK_GUARD_ONLY)
  Test<LockGuardTester>();
#elif defined(UNIQUE_LOCK_WITHOUT_DEFERRING)
  Test<NonDeferringUniqueLock>();
#elif defined(UNIQUE_LOCK_WITH_DEFERRING)
  Test<DeferringUniqueLock>();
#endif

  return 0;
}


