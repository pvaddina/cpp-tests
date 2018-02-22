#include <iostream>
#include <string>
#include <map>
#include <algorithm>

struct temp
{
    temp(int v) : value(v) {}
#ifdef NOT_COPYABLE
    temp(const temp&) = delete;
#endif
    void operator=(const temp&) = delete;
    int value;
};

int main()
{
    std::map<std::string, temp> v;
    v.insert(std::make_pair("xxxxx", temp(1)));
    v.insert(std::make_pair("Two", temp(233)));
    v.insert(std::make_pair("Four", temp(4)));
    v.insert(std::make_pair("Five", temp(5)));
    v.insert(std::make_pair("Three", temp(437)));
    
    std::for_each(v.begin(), v.end(), [](const std::pair<std::string, temp>& lclV) { std::cout << lclV.first << "-" << lclV.second.value << std::endl; });
    
    std::map<std::string, temp> vCopy;
    vCopy = v;
    #if 0
    std::cout << "\nAfter copy" << std::endl;
    
    std::for_each(v.begin(), v.end(), [](const std::pair<std::string, int>& lclV) { std::cout << lclV.first << "-" << lclV.second << std::endl; });
    std::for_each(vCopy.begin(), vCopy.end(), [](const std::pair<std::string, int>& lclV) { std::cout << lclV.first << "-" << lclV.second << std::endl; });
    #endif
        
    return 0;
}
    
    
    
