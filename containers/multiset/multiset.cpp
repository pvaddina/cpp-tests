#include <iostream>
#include <set>

template <typename T>
void Print(std::string_view str, const std::multiset<T>& mset)
{
    std::cout << str << ":";
    for (const auto& val: mset)
        std::cout << val << " ";
    std::cout << "\n";
}

void Inittests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Inittests\n";
    std::multiset<int> mset {1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 3, 2, 4};
    Print("Initializer list initialization", mset);
}

void EqualRangeTest()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Working with duplicate values\n";
    std::multiset<int> mset {1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 3, 2, 4};

    auto eqrangepair = mset.equal_range(2);
    std::cout << "Distance=" << std::distance(eqrangepair.first, eqrangepair.second) << ", count=" << mset.count(2) << std::endl;

    mset.erase(eqrangepair.first, eqrangepair.second);
    Print("After deleting the duplicates", mset);
}


int main()
{
    Inittests();
    EqualRangeTest();
    return 0;
}

