#include <iostream>

struct AReq {void Print() { std::cout << "AReq" << std::endl; } };
struct BReq {void Print() { std::cout << "BReq" << std::endl; } };
struct CReq {void Print() { std::cout << "CReq" << std::endl; } };

struct ACnf {void PrintCnf() { std::cout << "ACnf" << std::endl; } };
struct BCnf {void PrintCnf() { std::cout << "BCnf" << std::endl; } };
struct CCnf {void PrintCnf() { std::cout << "CCnf" << std::endl; } };

template <typename T> struct TypId { typedef T REQ; };

template<> struct TypId<ACnf> { typedef ACnf CNF; };
template<> struct TypId<BCnf> { typedef BCnf CNF; };
template<> struct TypId<CCnf> { typedef CCnf CNF; };

template <typename T>
void SimplePrint(typename TypId<T>::REQ &t)
{
   t.Print();
}

template <typename T>
void SimplePrint(typename TypId<T>::CNF &t)
{
   t.PrintCnf();
}

int main()
{
   AReq a;
   CCnf c;
   SimplePrint<AReq>(a);
   SimplePrint<CCnf>(c);

   return 0;
}

