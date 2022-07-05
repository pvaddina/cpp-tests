#include <iostream>
#include <string>
#include <optional>

namespace CVar
{
    struct Identify
    {
        int id = 999;
        std::string name = "Triple name";
        std::string Print()
        {
            return std::to_string(id) + " " + name;
        }
    };

    class CVariable
    {
        private:
        std::optional<int> mVar = std::nullopt;
        std::optional<Identify> mIdentify = std::nullopt;

        public:
        CVariable()
        : mVar(437)
        , mIdentify(Identify())
        {}
        void Print()
        {
            std::cout << mVar.value() << " " << mIdentify.value().Print() << std::endl;
        }
    };

    void Test()
    {
        CVariable var;
        var.Print();
    }
}