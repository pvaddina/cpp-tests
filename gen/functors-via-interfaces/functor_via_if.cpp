#include <iostream>
#include <string>
#include <map>
#include <algorithm>

struct CallableIf
{
    virtual void operator()(const std::map<std::string, int>::value_type& s) = 0;
};

struct ValueHolder : public CallableIf
{
    ValueHolder() : value(999999) {}
    void operator()(const std::map<std::string, int>::value_type& s)
    {
        if (s.first == "Four")
        {
            value = s.second;
            std::cout << "Value is " << value << std::endl;
        }
    }
    int value;
};

struct ValuePrinter : public CallableIf
{
    void operator()(const std::map<std::string, int>::value_type& s)
    {
        std::cout << s.first << "-" << s.second << std::endl;
    }
};

struct Functor
{
    CallableIf* pCallable;
    void operator()(const std::map<std::string, int>::value_type& s) { (*pCallable)(s); } 
};

void OnEachItem(const std::map<std::string, int>& m, CallableIf& pC)
{
    Functor f;
    f.pCallable = &pC;
    std::for_each(m.begin(), m.end(), f);
}

int main()
{
    std::map<std::string, int> v;
    v.insert(std::make_pair("xxxxx", 1));
    v.insert(std::make_pair("Two", 233));
    v.insert(std::make_pair("Four", 4));
    v.insert(std::make_pair("Five", 5));
    v.insert(std::make_pair("Three", 437));
    
    ValueHolder v1;
    ValuePrinter v2;

    OnEachItem(v, v1);
    std::cout << "\n\n";
    OnEachItem(v, v2);

    return 0;
}
    
    
    
