#include <iostream>

typedef int SInt32;

typedef bool (*FCheck)(SInt32, SInt32);

template <FCheck CheckFunc>
class Counter
{
  public:
    Counter(const SInt32 c, const SInt32 l) : count(c), limit(l) {}
    Counter& operator++()
    {
      if (CheckFunc( count+1, limit ))
      {
        ++count;
      }
      return *this;
    }

    Counter& operator--()
    {
      if (CheckFunc( count-1, limit ))
      {
        --count;
      }
      return *this;
    }

    Counter& operator+=(int c)
    {
      int temp = count + c;
      if (CheckFunc( temp, limit ))
      {
        count = temp;
      }
      return *this;
    }

    Counter& operator-=(int c)
    {
      int temp = count - c;
      if (CheckFunc( temp, limit ))
      {
        count = temp;
      }
      return *this;
    }

    SInt32 GetCount() { return count; }
  protected:
    SInt32  limit;
    SInt32  count;
};

bool MaxCheck(const SInt32 ctr, const SInt32 ulimit)
{ 
  return ctr < ulimit; 
}

bool MinCheck(const SInt32 ctr, const SInt32 llimit)
{ 
  return ctr > llimit; 
}


typedef Counter<MaxCheck> MaxCounter;
typedef Counter<MinCheck> MinCounter;

void test1()
{
  MaxCounter c(3, 7);
  ++c;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  ++c;
  ++c;
  ++c;
  ++c;
  ++c;
  ++c;
  ++c;
  std::cout << c.GetCount() << std::endl;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  --c;
  std::cout << c.GetCount() << std::endl;
}

int main()
{
  test1();

  return 0;
}







