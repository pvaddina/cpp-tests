#include <iostream>

struct MsgOneReq { void getName() { std::cout << "MsgOneReq" << std::endl; } };
struct MsgTwoReq { void getName() { std::cout << "MsgTwoReq" << std::endl; } };
struct MsgThreeReq { void getName() { std::cout << "MsgThreeReq" << std::endl; } };
struct MsgFourReq { void getName() { std::cout << "MsgFourReq" << std::endl; } };
struct MsgFiveReq { void getName() { std::cout << "MsgFiveReq" << std::endl; } };
struct MsgSixReq { void getName() { std::cout << "MsgSixReq" << std::endl; } };

struct MsgOneCnf { void getName() { std::cout << "MsgOneCnf" << std::endl; } };
struct MsgTwoCnf { void getName() { std::cout << "MsgTwoCnf" << std::endl; } };
struct MsgThreeCnf { void getMyName() { std::cout << "MsgThreeCnf" << std::endl; } };
struct MsgFourCnf { void getMyName() { std::cout << "MsgFourCnf" << std::endl; } };
struct MsgFiveCnf { void getOtherName() { std::cout << "MsgFiveCnf" << std::endl; } };
struct MsgSixCnf { void getOtherName() { std::cout << "MsgSixCnf" << std::endl; } };

template <typename T> struct CnfTraits{typedef T OTHERS; };
template <> struct CnfTraits<MsgOneReq>{ typedef MsgOneReq T1; typedef MsgOneCnf CNF; };
template <> struct CnfTraits<MsgTwoReq>{ typedef MsgTwoReq T1; typedef MsgTwoCnf CNF; };
template <> struct CnfTraits<MsgThreeReq>{ typedef MsgThreeReq T2; typedef MsgThreeCnf CNF; };
template <> struct CnfTraits<MsgFourReq>{ typedef MsgFourReq T2; typedef MsgFourCnf CNF; };


template <typename T>
void Print(typename CnfTraits<T>::T1& msg)
{
  typename CnfTraits<T>::CNF cnf;
  cnf.getName();
}

template <typename T>
void Print(typename CnfTraits<T>::T2& msg)
{
  typename CnfTraits<T>::CNF cnf;
  cnf.getMyName();
}

template <typename>
void Print(MsgFiveReq& msg)
{
  MsgFiveCnf cnf;
  cnf.getOtherName();
}

template <typename>
void Print(MsgSixReq& msg)
{
  MsgSixCnf cnf;
  cnf.getOtherName();
}


template <typename T>
void PrintAll(T& msg)
{
  Print<T>(msg);
}
  
  

int main()
{
  MsgOneReq one;
  MsgTwoReq two;
  MsgThreeReq three;
  MsgFourReq four;
  MsgFiveReq five;
  MsgSixReq six;

  PrintAll(one);
  PrintAll(two);
  PrintAll(three);
  PrintAll(four);
  PrintAll(five);
  PrintAll(six);

  return 0;
}

