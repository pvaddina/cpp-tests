#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <mutex>

const int MAX_VALUE = 100;
const int MAX_THREADS = 10;

std::vector<int> threadVec;
std::mutex m;

void FillVec()
{
  //auto sumup = [](int a, int b) { return a+b; }
  //std::for_each(threadVec.begin(), 
  int fill=0;
  for (int i = 0; i<MAX_VALUE; ++i, ++fill)
  {
    if ( fill == 10 ) { fill = 0; }
    threadVec.push_back(fill);
  }

  std::for_each(threadVec.begin(), threadVec.end(), [](const int& a) { std::cout << a << " "; });
  std::cout << std::endl;
}

void tBody(const int start, const int end)
{
  const int newStart = start;
  int finalVal = 0;
  std::thread::id id= std::this_thread::get_id();

  auto sumup = [finalVal, id](int& a) mutable -> void { 
    a = finalVal+a; 
    finalVal = a; 
  };

#if 0
  std::vector<int>::iterator iter = threadVec.begin();
  for (int i=newStart; i<end-newStart; ++i)
  {
    std::vector<int>::iterator s = iter+i;
    std::vector<int>::iterator e = iter+end;
    std::for_each(s, e, sumup);
  }
#endif

  std::lock_guard<std::mutex> lock{m};
  std::cout << std::endl << std::endl;
  std::vector<int>::iterator s = threadVec.begin()+newStart;
  std::vector<int>::iterator e = threadVec.begin()+end;
  std::for_each(s, e, [](const int& a) { std::cout << a << " "; });
  std::stringstream o;
  o << "id:" << id << "=" << std::accumulate(s, e, 0) << ", newStart=" << newStart << ", end=" << end << std::ends;
  std::cout << o.str() << std::endl;
}

int main()
{
  FillVec();
  std::vector<std::thread> threads;
  const int max_value_per_thread = MAX_VALUE/MAX_THREADS;

  for (int i=0; i<MAX_THREADS; ++i)
  {
    const int start = i * max_value_per_thread;
    threads.push_back(std::thread(tBody, start, start + max_value_per_thread));
  }
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

  return 0;
}

