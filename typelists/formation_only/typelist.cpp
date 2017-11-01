#include <iostream>

struct NoType {};
struct OneReq{ void PName() const { std::cout << "This is OneReq" << std::endl; } };
struct TwoReq{ void PName() const { std::cout << "This is TwoReq" << std::endl; } };
struct ThreeReq{ void PName() const { std::cout << "This is ThreeReq" << std::endl; } };


template <typename T1=NoType, typename T2=NoType, typename T3=NoType> struct TypeList;
template <typename T1, typename T2, typename T3> struct TypeList
{
	typedef T1 Head;
	typedef TypeList<T2, T3> Tail;
};

template <> struct TypeList<NoType, NoType> {};

int main()
{
	typedef TypeList<OneReq, TwoReq, ThreeReq>::Head AllType;

	return 0;
}

