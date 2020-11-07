#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

class Doo {}d;
class Eoo {}e;
class Foo {
    public:
        //virtual ~Foo() = default;
}f;
class Goo {}g;


namespace T
{
    class DFoo : public Foo
    {
        public:
            ~DFoo() { std::cout << "In the destructor of DFoo" << std::endl; }
    };
    
    void Test()
    {
        Foo* f = new DFoo;
        delete f;
    }
}
    

    
namespace T2
{
    template <typename T>
    typename std::enable_if<std::is_same<T,Doo>::value>::type IsDefined(T&) { std::cout << "Doo is accepted" << std::endl; }
    
    template <typename T>
    typename std::enable_if<std::is_same<T,Eoo>::value>::type IsDefined(T&) { std::cout << "Eoo is accepted" << std::endl; }
    
    template <typename T>
    typename std::enable_if<std::is_same<T,Foo>::value>::type IsDefined(T&) { std::cout << "Foo is accepted" << std::endl; }

    template <typename T>
    typename std::enable_if<!std::is_same<T,Doo>::value
                         && !std::is_same<T,Eoo>::value
                         && !std::is_same<T,Foo>::value>::type IsDefined(T&) { std::cout << "T is not accepted" << std::endl; }

    void Test()
    {
        IsDefined(d);
        IsDefined(e);
        IsDefined(f);
        IsDefined(g);
    }
}

    

    
namespace T3
{
    static constexpr int GlobalConst1 = 437;
    static constexpr int GlobalConst2 = 999;
    static constexpr int GlobalConst3 = 1111;
    
    void Test(const int val)
    {
        auto gt1 = [&] (const int v) -> bool { return v >= GlobalConst1; };
        auto gt2 = [&] (const int v) -> bool { return v >= GlobalConst2; };
        auto gt3 = [&] (const int v) -> bool { return v >= GlobalConst3; };

        auto lessThan1    = [&](const int v) -> bool { return !gt1(v); };
        auto between1_2   = [&](const int v) -> bool { return gt1(v) && !gt2(v); };
        auto between2_3   = [&](const int v) -> bool { return gt2(v) && !gt3(v); };
        //auto between1_3   = [&](const int v) -> bool { return gt1(v) && !gt3(v); };
        auto greaterThan3 = [&](const int v) -> bool { return gt3(v); };
        
        if ( lessThan1(val) )
            std::cout << val << " < " << GlobalConst1 << std::endl;
        else if ( between1_2(val) )
            std::cout << GlobalConst1 << " <= " << val << " <= " << GlobalConst2 << std::endl;
        else if ( between2_3(val) )
            std::cout << GlobalConst2 << " <= " << val << " <= " << GlobalConst3 << std::endl;
        else if ( greaterThan3(val) )
            std::cout << val << " > " << GlobalConst3 << std::endl;
        
    }
}

int main()
{
    T3::Test(4);
    T3::Test(400);
    T3::Test(500);
    T3::Test(600);
    T3::Test(900);
    T3::Test(999);
    T3::Test(1100);
    T3::Test(1110);
    T3::Test(1200);
    T3::Test(2000);
    return 0;
}

