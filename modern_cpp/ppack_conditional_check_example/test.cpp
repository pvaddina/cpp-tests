#include <iostream>
#include <type_traits>

template <typename DST, typename... Ts>
void SetValue(DST& dst, Ts&&... ts)
{
  CheckAndSetVal(dst, std::forward<Ts>(ts)...);
}

template <typename DST>
void CheckAndSetVal(DST&) {}

template <typename DST, typename T1, typename T2, typename... Ts>
std::enable_if_t<std::is_same_v<DST, T2> > CheckAndSetVal(DST& dst, T1&& cond, T2&& val, Ts&&... ts)
{
  if (cond())
    dst = val;
  else
    CheckAndSetVal(dst, std::forward<Ts>(ts)...);
}

template <typename DST, typename T1, typename T2, typename... Ts>
std::enable_if_t<!std::is_same_v<DST, T2> > CheckAndSetVal(DST& dst, T1&& cond, T2&& val, Ts&&... ts)
{
  if (cond())
    dst = val();
  else
    CheckAndSetVal(dst, std::forward<Ts>(ts)...);
}


int main()
{
  int i;
  SetValue(i, []() { return false; }, 444
            , []() { return false; }, 999
            , []() { return true; }, []() { return 222; });

  std::cout << i << std::endl;

  int j;
  SetValue(j, []() { return false; }, 444
            , []() { return true; }, 999
            , []() { return true; }, []() { return 222; });

  std::cout << j << std::endl;

  int z = 0;
  SetValue(z, []() { return false; }, 444
            , []() { return false; }, 999
            , []() { return false; }, []() { return 222; });

  std::cout << z << std::endl;

  return 0;
}

