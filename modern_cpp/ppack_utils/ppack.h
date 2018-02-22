// The terminator type
struct TypTerminator {};


template <typename Ts...>
struct TypeList
{
};

// Assign an ID to each type based on their positioning within the list
template <typename... Ts>
int GetCount(Ts... ts)
{ 
  return sizeof...(ts);
};

