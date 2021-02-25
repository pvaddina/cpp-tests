#include <string>
#include <map>

int VAL = 999;
std::map<int,std::string> NUM_MAP = 
{
    {98, "98"},
    {99, "99"},
    {100, "100"},
};

namespace T1
{
    std::string NON_CONST_NAME = "NON_CONST_NAME";
    extern const std::string NAME = "NAME";
}
