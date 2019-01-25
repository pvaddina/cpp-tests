#pragma once

#include <type_traits>

namespace SFINAE
{
  template <typename DST>
  void CheckAndSetVal(DST&) {}

  template <typename DST, typename T1, typename T2, typename... Ts>
  std::enable_if_t<!std::is_same_v<DST, T2> > CheckAndSetVal(DST& dst, T1&& cond, T2&& val, Ts&&... ts);

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

  template <typename DST, typename... Ts>
  void SetValue(DST& dst, Ts&&... ts)
  {
    CheckAndSetVal(dst, std::forward<Ts>(ts)...);
  }

}

