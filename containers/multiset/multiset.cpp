#include <iostream>
#include <set>

void Test1()
{
    std::multiset<int> mset {1, 2, 3, 4, 5, 6, 7, 2, 3, 4, 5, 3, 2, 4};
    auto res = mset.equal_range(2);
    std::cout << "Distance=" << std::distance(res.first, res.second) << ", count=" << mset.count(2) << std::endl;
}


int main()
{
    Test1();
    return 0;
}

