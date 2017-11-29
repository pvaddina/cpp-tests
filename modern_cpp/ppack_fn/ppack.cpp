#include <iostream>
#include <string>

template <typename T> struct Prop 
{ 
  Prop(T v) { prop = v; }
  void Print() const { std::cout << prop; }
  T prop; 
};

using Speed = double;
using Gear = int;
using RadioStation = std::string;

class DContainer
{
  public:
    DContainer()
      : speed{0.0}
      , gear{0}
      , rSt{"NOTHING"}
    {
    }
    void Set(Prop<Speed>& s) 
    { 
      std::cout << "Setting speed ... " << std::endl;
      speed.prop = s.prop; 
    }
    void Set(Prop<Gear>& s)
    { 
      std::cout << "Setting Gear ... " << std::endl;
      gear.prop = s.prop;  
    }
    void Set(Prop<RadioStation>& s) 
    { 
      std::cout << "Setting the RadioStation... " << std::endl;
      rSt.prop = s.prop; 
    }

    void PrintAll() 
    {
      std::cout << "Current Car Properties: Speed=" << speed.prop << "; Gear=" << gear.prop <<  "; RadioStation=" << rSt.prop << std::endl << std::endl;
    }

  private:
    Prop<Speed> speed;
    Prop<Gear>  gear;
    Prop<RadioStation> rSt;
};

template<typename T>
void SetAllAtOnce(DContainer& obj, T& v)
{
  obj.Set(v);
  obj.PrintAll();
}

template <typename T, typename... Ts>
void SetAllAtOnce(DContainer& obj, T& val, Ts... args)
{
  obj.Set(val);
  obj.PrintAll();
  SetAllAtOnce(obj, args...);
}

int main()
{
  DContainer d;
  Prop<Speed> speed1{150};
  Prop<Speed> speed2{200};
  Prop<Speed> speed3{250};
  Prop<Gear>  gear1{5};
  Prop<Gear>  gear2{6};
  Prop<Gear>  gear3{7};
  Prop<RadioStation> rSt{"Radio Mars"};

  SetAllAtOnce(d, rSt, gear1, speed1, gear2, speed2, gear3, speed3);

  return 0;
}
