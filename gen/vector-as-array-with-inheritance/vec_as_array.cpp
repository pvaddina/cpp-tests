#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

struct Base
{
    Base() : p(0) {}
    char* p;
    void PrintPointer() { std::cout << "pointer=" << (void*)p << ", value=" << p << std::endl; }
};

struct Der : public Base
{
    public:
        Der(const std::string& iS) : s(iS) 
        {
            p = const_cast<char*>(s.c_str());
            PrintPointer();
        }
        
        Der(const Der& d)
        {
            //std::cout << "In copy constructor" << std::endl;
            s = d.s;
            p = const_cast<char*>(s.c_str());
        }

    public:
        std::string s;
};

std::vector<Der> v;
std::string sArrays[] = {"one", "two", "three", "four", "five", "six" };

void AddStr(const int idx)
{
    switch(idx)
    {
        case 0:
        {
        const char* pTemp = "one";
        v.push_back(Der(pTemp));
        break;
        }

        case 1:
        {
        const char* pTemp = "two";
        v.push_back(Der(pTemp));
        break;
        }

        case 2:
        {
        const char* pTemp = "three";
        v.push_back(Der(pTemp));
        break;
        }

        case 3:
        {
        const char* pTemp = "four";
        v.push_back(Der(pTemp));
        break;
        }

        case 4:
        {
        const char* pTemp = "five";
        v.push_back(Der(pTemp));
        break;
        }

        case 5:
        {
        const char* pTemp = "six";
        v.push_back(Der(pTemp));
        break;
        }
    }
}

int main()
{    
    AddStr(0);
    v[0].PrintPointer();
    AddStr(1);
    v[1].PrintPointer();
    AddStr(2);
    v[2].PrintPointer();
    AddStr(3);
    v[3].PrintPointer();
    AddStr(4);
    v[4].PrintPointer();
    AddStr(5);
    v[5].PrintPointer();
    
    std::vector<Der>::iterator it = v.begin();
    while(it != v.end())
    {
        std::cout << "std::string=" << it->s << ", char*=" << it->p << ", and pointer=" << (void*)(it->p) << std::endl;
        ++it;
    }
    
    return 0;
}
    
    
    
