#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

struct Base
{
    char* p;
};

struct Der : public Base
{
    Der(std::string s, const int i) : name(s), id(i) 
    {
        p = const_cast<char*>(name.c_str());
    }
    
    Der(const Der& d)
    {
        name = d.name;
        id = d.id;
        p = const_cast<char*>(name.c_str());
    }
    std::string name;
    int id;
};

void PrintBase(const int num, Base* pBase)
{
    for (int i=0; i<num; ++i)
    {
        std::cout << "Str=" << pBase->p << std::endl;
        pBase = static_cast<Base*>(static_cast<Der*>(pBase) + 1);
    }
}

void PrintDer(const int num, Der* pDer)
{
    for (int i=0; i<num; ++i)
    {
        std::cout << "name=" << pDer->name << ", id=" << pDer->id << std::endl;
        ++pDer;
    }
}

std::vector<Der> v;

int main()
{
    Der one = Der("one", 1);
    v.push_back(one);
    Der two = Der("two", 2);
    v.push_back(two);
    Der three = Der("three", 3);
    v.push_back(three);
    Der four = Der("four", 4);
    v.push_back(four);
    
    PrintBase(v.size(), &v[0]);
    
    return 0;
}
    
    
    
