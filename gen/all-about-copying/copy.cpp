#include <iostream>
#include <string>

struct Basic
{
    int a;
    double b;
    void Print(const std::string& ip)
    {
      std::cout << ip << ": a=" << a << ", b=" << b << std::endl;
    }
};


void StructCopyTest()
{
    Basic objBasic;
    objBasic.Print("Default Initialization of objBasic");
    
    Basic objBasic0 {23, 545.8787};
    objBasic0.Print("Field initialization with Braces, objBasic0");
    
    Basic objBasic1;
    objBasic1.Print("Default Initialization of objBasic1");
    objBasic1.a = 437;
    objBasic1.b = 437.437;
    objBasic1.Print("Initialize the values individually, objBasic1");
    
    Basic objBasic2;
    objBasic2 = objBasic1;
    objBasic2.Print("Copying objBasic1 to objBasic2, objBasic2");
    
    Basic objBasic3(objBasic2);
    objBasic3.Print("Copy constructing objBasic3 from objBasic2, objBasic3");
}


int main()
{
    StructCopyTest();
    
    return 0;
}
