#pragma once

namespace ConstExpression
{
  template <typename DST, typename T1, typename T2, typename... Ts>
  void SetValue(DST& dst, T1&& cond, T2&& val, Ts&&... ts)
  {
    if (cond())
    {
      if constexpr(std::is_invocable_v<T2>)
        dst = val();
      else
        dst = val;
    }
    else if constexpr(sizeof...(Ts) > 0)
    {
      SetValue(dst, std::forward<Ts>(ts)...);
    }
  }
}

