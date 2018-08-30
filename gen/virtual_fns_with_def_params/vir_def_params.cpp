#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <functional>
#include <memory>

struct IParam
{
    virtual void PrintValue(const std::string s, const int v=999) = 0;
};

struct BaseParam : public IParam
{
    BaseParam() {}
    virtual void PrintValue(const std::string s, const int v)
    {
        std::cout << "BaseParam:" << s << "=" << v << std::endl;
    }
};

struct NewBaseParam : public IParam
{
    NewBaseParam() {}
    virtual void PrintValue(const std::string s, const int v)
    {
        std::cout << "NewBaseParam:" << s << "=" << v << std::endl;
    }
};


int main()
{
    IParam* p;
    p = new BaseParam;
    p->PrintValue(std::string("This is a temp string"));
    
    p = new NewBaseParam;
    p->PrintValue(std::string("This is a temp string"));
    return 0;
}
