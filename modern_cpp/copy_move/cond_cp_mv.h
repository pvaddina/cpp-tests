#include <iostream>
#include <type_traits>

namespace T2
{
    template <bool ALLOW_COPY, bool ALLOW_MOVE>
    struct A 
    {
        using Base = A<ALLOW_COPY, ALLOW_MOVE>;
        
        A(int v) : value(v) {}
        
        template <bool T = ALLOW_COPY>
        A(const typename std::enable_if<T==true, Base>::type& a) { value = a.value; }
        template <bool T = ALLOW_COPY>
        A(typename std::enable_if<T==false, Base>::type&) = delete;
        
        template <bool T = ALLOW_MOVE>
        A(typename std::enable_if<T==true, Base>::type&& a) { value = a.value; a.value = 0; }
        template <bool T = ALLOW_MOVE>
        A(typename std::enable_if<T==false, Base>::type&&) = delete;
        
        int value = 437;
        void Print() { std::cout << value << std::endl; } 
    };

    void Test()
    {
        A<true, true> a1 { 999 };
        a1.Print();
        auto a2{ a1 };
        a2.Print();
        
        A<false, false> a3 { 888 };
        a3.Print();
        //A<false, false> a4 { a3 };

        A<false, true> a5 { 777 };
        a5.Print();
        A<false, true> a6 { std::move(a5) };
    }
}



