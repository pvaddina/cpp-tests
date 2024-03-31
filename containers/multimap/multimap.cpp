#include <iostream>
#include <map>
#include <string>

void Test1()
{
    std::multimap<int,std::string> mset {{1, "one"}
                                        ,{2, "two"}
                                        , {3, "three"}
                                        , {4, "four"}
                                        , {5, "five"}
                                        , {6, "six"}
                                        , {7, "sdfds"}
                                        , {2, "sdfsf"}};
    auto res = mset.equal_range(2);
    for (auto it = res.first; it != res.second; ++it)
    {
        std::cout << it->first << "-" << it->second << std::endl;
    }
}


void Test2()
{
    std::multimap<int,std::string> mset {{1, "one"}
                                        ,{2, "two"}
                                        , {3, "three"}
                                        , {4, "four"}
                                        , {5, "five"}
                                        , {6, "six"}
                                        , {7, "sdfds"}
                                        , {2, "sdfsf"}};
    auto item = mset.extract(2);
    std::cout << "key=" << item.key() << ", mapped=" << item.mapped() << std::endl;
    item.mapped() = "some new value";
    mset.insert(std::move(item));

    for (auto& [k,v]: mset)
        std::cout << "key=" << k << ", value=" << v << std::endl;
}


int main()
{
    Test1();
    Test2();
    return 0;
}

