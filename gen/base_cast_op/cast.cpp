#include <iostream>
#include <string>

struct A 
{
    A() : a(437), b("Test string") {}
    int a;
    std::string b;
};

struct B : public A
{
    B() : a(438), b('$') {}
    int a;
    char b;
};

struct C : public B
{
    C() : a(439), b(22.345) {}
    int a;
    double b;
};

struct D : public C
{
    D() : a(440), b(99999) {}
    int a;
    int b;
};

int main()
{
    D d;
    std::cout << static_cast<A>(d).a << " - " << static_cast<A>(d).b << std::endl;
    std::cout << static_cast<B>(d).a << " - " << static_cast<B>(d).b << std::endl;
    std::cout << static_cast<C>(d).a << " - " << static_cast<C>(d).b << std::endl;
    std::cout << static_cast<D>(d).a << " - " << static_cast<D>(d).b << std::endl;
}

