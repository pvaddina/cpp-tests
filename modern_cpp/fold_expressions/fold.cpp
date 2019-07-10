#include <iostream>


// From: https://en.cppreference.com/w/cpp/language/fold
// Types of Fold expressions and their expansions
// 1) Unary right fold (E op ...) becomes (E1 op (... op (EN-1 op EN)))
// 2) Unary left fold (... op E) becomes (((E1 op E2) op ...) op EN)
// 3) Binary right fold (E op ... op I) becomes (E1 op (... op (EN−1 op (EN op I))))
// 4) Binary left fold (I op ... op E) becomes ((((I op E1) op E2) op ...) op EN)

namespace T1
{
    template <typename T>
    void SingleOut(const T& t)
    {
        std::cout << t << " ";
    }
    
    template <typename... Ts>
    void DirectPrint(Ts&&... ts)
    {
        // A fold expression of the form:
        // (I op ... op E)
        // I   --> std::cout
        // op  --> <<
        (std::cout << ... << ts);
    }
    
    template <typename... Ts>
    void SpacePrint(Ts&&... ts)
    {
        // A fold expression of the form:
        // (... op E)
        // op  --> ,
        (... , SingleOut(ts));
        std::cout << "\n";

        // A fold expression of the form:
        // (E op ...)
        // op  --> ,
        (SingleOut(ts) , ...);
    } 
    
    template <typename... Ts>
    void NewlinePrint(Ts&&... ts)
    {
        (SingleOut(ts) , ... , SingleOut("\n"));
        std::cout << "On a new line, but with a space character at the beginning";
    } 
    
    void PrintTest()
    {
        DirectPrint("Fold", "is", "a", "C++", 17, "Feature");
        std::cout << '\n';
        SpacePrint("Fold", "is", "a", "C++", 17, "Feature");
        std::cout << '\n';
        NewlinePrint("Fold", "is", "a", "C++", 17, "Feature");
    }
}



int main()
{
    T1::PrintTest();
}

