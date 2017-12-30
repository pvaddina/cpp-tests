#include <iostream>

typedef int SInt32;

typedef bool (*FCheck)(SInt32, SInt32, SInt32);
typedef void (*FInit)(SInt32&, SInt32&, SInt32&, const SInt32, const SInt32, const SInt32);

template <FCheck CheckFunc, FInit InitFunc>
class Counter
{
  public:
    Counter(const SInt32 c, const SInt32 l=0, const SInt32 u=0) { InitFunc(count, llimit, ulimit, c, l, u); }
    Counter& operator++()
    {
      if (CheckFunc( count+1, llimit, ulimit )) { ++count; }
      return *this;
    }

    Counter& operator--()
    {
      if (CheckFunc( count-1, llimit, ulimit )) { --count; }
      return *this;
    }

    Counter& operator+=(int c)
    {
      int temp = count + c;
      if (CheckFunc( temp, llimit, ulimit )) { count = temp; }
      return *this;
    }

    Counter& operator-=(int c)
    {
      int temp = count - c;
      if (CheckFunc( temp, llimit, ulimit )) { count = temp; }
      return *this;
    }

    bool operator>=(int val)
    {
      return count >= val;
    }

    bool operator<=(int val)
    {
      return count <= val;
    }

    SInt32 GetCount() { return count; }

  protected:
    SInt32  llimit;
    SInt32  ulimit;
    SInt32  count;
};


struct None
{
  static void Init(SInt32& ctr, SInt32& llimit, SInt32& ulimit, const SInt32 c, const SInt32 l, const SInt32 u)
  { 
    ctr    = c;
    llimit = 0;
    ulimit = 0;
  }
  static bool Check(const SInt32 ctr, const SInt32 llimit, const SInt32 ulimit) { return true; }
};


struct Max
{
  static void Init(SInt32& ctr, SInt32& llimit, SInt32& ulimit, const SInt32 c, const SInt32 u, const SInt32 invalid)
  { 
    ctr    = c;
    llimit = 0;
    ulimit = u;
  }

  template <bool (*F)(SInt32, SInt32)>
  static bool Check(const SInt32 ctr, const SInt32 llimit, const SInt32 ulimit) { return F(ctr, ulimit); }
};
bool MaxCheckStrict(const SInt32 ctr, const SInt32 ulimit) { return ctr < ulimit; }
bool MaxCheckLoose(const SInt32 ctr, const SInt32 ulimit) { return ctr <= ulimit; }

struct Min
{
  static void Init(SInt32& ctr, SInt32& llimit, SInt32& ulimit, const SInt32 c, const SInt32 l, const SInt32 invalid)
  { 
    ctr    = c;
    llimit = l;
    ulimit = 0;
  }

  template <bool (*F)(SInt32, SInt32)>
  static bool Check(const SInt32 ctr, const SInt32 llimit, const SInt32 ulimit) { return F(ctr, llimit); }
};
bool MinCheckStrict(const SInt32 ctr, const SInt32 ulimit) { return ctr > ulimit; }
bool MinCheckLoose(const SInt32 ctr, const SInt32 ulimit) { return ctr >= ulimit; }

struct MinMax
{
  static void Init(SInt32& ctr, SInt32& llimit, SInt32& ulimit, const SInt32 c, const SInt32 l, const SInt32 u) 
  { 
    ctr    = c;
    llimit = l;
    ulimit = u;
  }

  template <bool (*FMin)(SInt32, SInt32), bool (*FMax)(SInt32, SInt32)>
  static bool Check(const SInt32 ctr, const SInt32 llimit, const SInt32 ulimit) { return FMin(ctr, llimit) && FMax(ctr, ulimit); }
};

typedef Counter< Max::Check<MaxCheckStrict>, Max::Init >  MaxCounter;
typedef Counter< MinMax::Check<MinCheckLoose, MaxCheckLoose>, MinMax::Init > MinMaxCounter;
typedef Counter< None::Check, None::Init > SimpleCounter;
#if 0
typedef Counter< Max<MaxCheckLoose>::Check >   LMaxCounter;
typedef Counter< Min<MinCheckStrict>::Check >  MinCounter;
typedef Counter< Min<MinCheckLoose>::Check >   LMinCounter;
//typedef Counter< MinMax::Check >  MinMaxCounter;
#endif

void MaxCtr1()
{
  MaxCounter c(3, 7);
  c+=5;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  c-=39;
  std::cout << c.GetCount() << std::endl;
}

void MinMaxCtr1()
{
  MinMaxCounter c(3, 0, 34);
  c-=39;
  std::cout << c.GetCount() << std::endl;
  c+=5;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
}

void SimpleCtr1()
{
  SimpleCounter c(2);
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  c+=2394;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;
  ++c;
  std::cout << c.GetCount() << std::endl;

  std::cout << (c >= 3456) << std::endl;
  std::cout << (c <= 3456) << std::endl;
}

int main()
{
  std::cout << std::endl << "MaxCtrl" << std::endl << "=============" << std::endl;
  MaxCtr1();

  std::cout << std::endl << "MinMaxCtr1" << std::endl << "=============" << std::endl;
  MinMaxCtr1();

  std::cout << std::endl << "SimpleCtrl" << std::endl << "=============" << std::endl;
  SimpleCtr1();

  return 0;
}








