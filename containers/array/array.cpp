#include <iostream>
#include <array>
#include <string>
#include <ostream>

void Print(const std::array<int,5>& arr)
{
    for (auto& val: arr)
    {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void InitTests()
{
    std::array<int,5> test{2,3,4,5,6};
    Print(test);

    std::array<int,5> test1 = {6,7,8,9,10};
    Print(test1);
}

void SizeTests()
{
    std::array<int,5> test{1,2,3};
    Print(test);
    std::cout << "Size=" << test.size() << ", Maxsize=" << test.max_size() << std::endl;
}

int main()
{
    InitTests();
    SizeTests();
    return 0;
}

