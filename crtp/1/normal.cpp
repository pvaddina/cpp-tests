#include <iostream>

struct MsgOneReq { void getName() { std::cout << "MsgOneReq" << std::endl; } };
struct MsgTwoReq { void getName() { std::cout << "MsgTwoReq" << std::endl; } };
struct MsgThreeReq { void getName() { std::cout << "MsgThreeReq" << std::endl; } };
struct MsgFourReq { void getName() { std::cout << "MsgFourReq" << std::endl; } };

struct MsgOneCnf { int Res; int one; void Print() { std::cout << "One: " << Res << " - " << one << std::endl; } };
struct MsgTwoCnf { int Res; int two; void Print() { std::cout << "Two: " << Res << " - " << two << std::endl;} };
struct MsgThreeCnf { int Res; void Print() { std::cout << "Three: " << Res << std::endl;} };
struct MsgFourCnf { int Res; void Print() { std::cout << "Four: " << Res << std::endl; } };


struct CnfRes
{
  template <typename MSG>
  void SetCnf(MSG& msg) { SetRes(msg); }

  template <typename MSG>
  void SetRes(MSG& msg) 
  { 
    std::cout << "In CnfRes" << std::endl;
    msg.Res = 435;
  }
};

typedef CnfRes GenCnfRes;

struct OneCnfRes : public CnfRes
{
  template <typename MSG>
  void SetRes(MSG& msg) 
  { 
    std::cout << "In OneCnfRes" << std::endl;
    msg.one=1; msg.Res = 9999999;
  }
};

struct TwoCnfRes : public CnfRes
{
  template <typename MSG>
  void SetRes(MSG& msg) 
  { 
    std::cout << "In TwoCnfRes" << std::endl;
    msg.two=2; msg.Res = 66666;
  }
};


int main()
{
  MsgOneCnf one;
  MsgTwoCnf two;
  MsgThreeCnf three;
  MsgFourCnf  four;

  GenCnfRes genCnfRes;
  OneCnfRes oneCnfRes;
  TwoCnfRes twoCnfRes;

  oneCnfRes.SetCnf(one);
  twoCnfRes.SetCnf(two);
  genCnfRes.SetCnf(three);
  genCnfRes.SetCnf(four);

  one.Print();
  two.Print();
  three.Print();
  four.Print();

  return 0;
}

