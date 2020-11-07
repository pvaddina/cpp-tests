#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace T1
{
    using MyTyp = std::unordered_map<std::string, std::vector<std::string> >;
    void Print(const std::string& label, const std::vector<std::string>& s)
    {
        std::cout << label;
        for (auto& item: s)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    void Print(const MyTyp& m)
    {
        for (auto& it: m)
        {
            std::cout << it.first << " has the following items: ";
            for (auto& p: it.second)
            {
                std::cout << p << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void SwapJillsItems(MyTyp& m)
    {
        std::vector<std::string> strangersPosessions { "QuantumComputer", "HDD", "iPhone15", "BankAccounts", "Porschecar" };
        m["Jill"].swap(strangersPosessions);
    }
    
    void Test()
    {
        std::vector<std::string> myPosessions { "HuaweiPhone", "Bag", "LenovoLaptop", "Papers", "OfficeID", "Food", "Drinks" };
        std::vector<std::string> wifePosessions { "SamsungPhone", "Bag", "DellLaptop", "NoPapers", "Jewellery", "NoFood", "NoDrinks" };
        MyTyp friendPosessions {
            {"Tom", {"Phone", "Bag", "Card", "CityPass"}},
            {"Jill", {"iPhone", "Jansport", "MvvCard", "R&SPass"}}
        };
        Print(friendPosessions);
        Print("My Posessions: ", myPosessions);
        Print("Wife's Posessions: ", wifePosessions);
        
        // Repace the posessions of "Tom" with that of "myPossessions"
        std::cout << "---------------------------------------------------------------\n";
        friendPosessions["Tom"].swap(myPosessions);
        Print(friendPosessions);
        Print("My Posessions: ", myPosessions);
        Print("Wife's Posessions: ", wifePosessions);
        
        // Repace the posessions of "Jills" with that of "wifePossessions"
        std::cout << "---------------------------------------------------------------\n";
        friendPosessions["Jill"].swap(wifePosessions);
        Print(friendPosessions);
        Print("My Posessions: ", myPosessions);
        Print("Wife's Posessions: ", wifePosessions);
        
        // Repace the posessions of "Jills" with that of "strangersPosessions"
        std::cout << "---------------------------------------------------------------\n";
        SwapJillsItems(friendPosessions);
        Print(friendPosessions);
        
        // Copy everything as it is to another map object
        std::cout << "---------------------------------------------------------------\n";
        auto temp = std::move(friendPosessions);
        std::cout << "FriendPosessions after Move:\n";
        Print(friendPosessions);
        std::cout << "temp after Move:\n";
        Print(temp);        
    }    
}

    

int main()
{
    T1::Test();    
    return 0;
}

