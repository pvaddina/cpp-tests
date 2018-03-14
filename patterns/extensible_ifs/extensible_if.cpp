#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <functional>
#include <memory>

struct BaseParam
{
    BaseParam() : v1(437), v2("Some test string") {}
    int v1;
    std::string v2;    
    virtual void GetV3(int& v) {}
};

struct If
{
    virtual void SupportSomething(const std::unique_ptr<BaseParam>& pPtr) const = 0;
    virtual BaseParam* GetBaseParam() const = 0;
};

struct CType1_LD : public If
{
    void SupportSomething(const std::unique_ptr<BaseParam>& pPtr) const
    {
        std::cout << pPtr->v1 << "---" << pPtr->v2 << std::endl;
    }
    virtual BaseParam* GetBaseParam() const { return new BaseParam; }
};

struct NewBaseParam : public BaseParam
{
    NewBaseParam() : v3(999) {}
    virtual void GetV3(int& v) 
    {
        v = v3;
    }    
    int v3;
};

struct CType2_LD : public If
{
    void SupportSomething(const std::unique_ptr<BaseParam>& pPtr) const
    {
        int v3 = 0;
        pPtr->GetV3(v3);
        std::cout << pPtr->v1 << "---" << pPtr->v2 << "---" << v3 << std::endl;
    }
    
    virtual BaseParam* GetBaseParam() const { return new NewBaseParam; }
};


void DoSomething(std::vector<std::unique_ptr<If> >& vec)
{
    std::vector<std::unique_ptr<If> >::iterator it = vec.begin();
    while(it != std::end(vec))
    {
        std::unique_ptr<BaseParam> p ((*it)->GetBaseParam());
        (*it)->SupportSomething(p);
        ++it;
    }
}


int main()
{
    std::vector<std::unique_ptr<If> > ifs;
    ifs.push_back(std::unique_ptr<If>(new CType1_LD));
    ifs.push_back(std::unique_ptr<If>(new CType2_LD));
    
    DoSomething(ifs);
    
    return 0;
}
