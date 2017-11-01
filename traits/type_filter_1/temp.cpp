#include <iostream>

struct MsgAReq { void PrintName(){ std::cout << "This is MsgAReq" << std::endl; } };
struct MsgBReq { void PrintName(){ std::cout << "This is MsgBReq" << std::endl; } };
struct MsgCReq { void PrintName(){ std::cout << "This is MsgCReq" << std::endl; } };
struct MsgDReq { void PrintName(){ std::cout << "This is MsgDReq" << std::endl; } };

struct MsgACnf { void PrintName(){ std::cout << "This is MsgACnf" << std::endl; } };
struct MsgBCnf { void PrintName(){ std::cout << "This is MsgBCnf" << std::endl; } };
struct MsgCCnf { void PrintName(){ std::cout << "This is MsgCCnf" << std::endl; } };

template <typename T> struct MsgProps {};
template <> struct MsgProps<MsgAReq> { typedef MsgAReq HASCNF; typedef MsgACnf CNF; };
template <> struct MsgProps<MsgBReq> { typedef MsgBReq HASCNF; typedef MsgBCnf CNF; };
template <> struct MsgProps<MsgCReq> { typedef MsgCReq HASCNF; typedef MsgCCnf CNF; };
template <> struct MsgProps<MsgDReq> { typedef MsgDReq HASNOCNF; };

template <typename T>
void Print(typename MsgProps<T>::HASCNF& req) { req.PrintName(); typename MsgProps<T>::CNF cnf; cnf.PrintName(); }
template <typename T>
void Print(typename MsgProps<T>::HASNOCNF& req) { req.PrintName(); }

int main()
{
  MsgAReq a;
  MsgBReq b;
  MsgCReq c;
  MsgDReq d;

  Print<MsgAReq>(a);
  Print<MsgBReq>(b);
  Print<MsgCReq>(c);
  Print<MsgDReq>(d);

  return 0;
}


