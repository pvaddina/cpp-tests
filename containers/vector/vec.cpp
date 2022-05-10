#include <iostream>
#include <vector>
#include <string>
#include <ostream>

template <typename T>
void Print(const std::string& s, const std::vector<T>& vToPrint)
{
    std::cout << s << ": ";
    for (const auto& v: vToPrint)
        std::cout << v << " ";
    std::cout << "\n";
}

struct TNoDefConstructor
{
    TNoDefConstructor() = delete;
    TNoDefConstructor(std::string&& s, int&& v) : name(std::move(s)), id(std::move(v)) {}
    friend std::ostream& operator<<(std::ostream& inStr, const TNoDefConstructor& c)
    {
        inStr << c.name << "," << c.id;
        return inStr;
    }
    private:
        std::string name;
        int id;
};

struct TDefConstructor
{
    TDefConstructor() = default;
    TDefConstructor(std::string&& s, int&& v) : name(std::move(s)), id(std::move(v)) {}
    TDefConstructor(const TDefConstructor& cpyObj) : name(cpyObj.name), id(cpyObj.id) {}
    TDefConstructor(const TDefConstructor&& cpyObj) : name(std::move(cpyObj.name)), id(cpyObj.id) {}
    TDefConstructor& operator=(const TDefConstructor& toCpyItem)
    {
        name = toCpyItem.name;
        id = toCpyItem.id;
        std::cout << "Copy assignment\n";
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& inStr, const TDefConstructor& c)
    {
        inStr << c.name << "," << c.id;
        return inStr;
    }
    private:
        std::string name = "Unknown";
        int id = 437;
};

void InitTests()
{
    // Initialization-1
    std::vector<int> one(3);  // Create a vector with 3 items initially
    Print("Size initialization of vector<int> with 3 items", one);

#if 0
    // Cannot use this kind of initialization because the default constructor 
    // is deleted for the structure
    std::vector<TNoDefConstructor> two(3);  // Create a vector with 3 items initially
    Print("Size initialization of vector<TNoDefConstructor> with 3 items", two);
#endif

    std::vector<TDefConstructor> three(3);  // Create a vector with 3 items initially
    Print("Size initialization of vector<TDefConstructor> with 3 items", three);

    TDefConstructor rep {"ICE", 626};
    auto it = three.begin();
    std::advance(it, 1);
    three.emplace(it, rep);
    Print("Printing after emplacing the second object of the vector", three);

    TDefConstructor plane {"Vistara", 938};
    std::cout << "Attempting insertion operation\n";
    three.insert(three.begin(), plane);
    Print("Printing after inserting an object at the very first location", three);

    auto start = three.begin();
    std::advance(start, 1);
    three.emplace(start, rep);
    Print("Initialize second object of the vector", three);
}


int main()
{
    InitTests();
    return 0;
}