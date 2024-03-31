#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>

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
    bool operator==(const TDefConstructor& cmpItem) const
    {
        return name==cmpItem.name && id==cmpItem.id;
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
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initialization tests\n";
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

    std::vector<TDefConstructor> four {{"Africa",1}, {"Asia",2}, {"Europe",3}, {"NorthAmerica",4}};
    Print("vector<TDefConstructor> initialization with default objects", four);
}

void InsertionTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Insertion tests\n";
    std::vector<TDefConstructor> three(3);  // Create a vector with 3 items initially

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

void FindTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Find tests\n";

    std::vector<TDefConstructor> two{{"Africa",8}, {"Asia",22}, {"Europe",3}, {"NorthAmerica",4}};
    Print("Contents of vector two", two);

    auto findItem = TDefConstructor{"Europe",3};
    auto it3 = std::find(two.begin(), two.end(), findItem);
    std::cout << "Item found with std::find " << *it3 << std::endl;

    auto it2 = std::find_if(two.begin(), two.end(), [&findItem](const auto& item) { return item==findItem; });
    std::cout << "Item found with std::find_if " << *it2 << std::endl;
}

void RemovalTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Removal tests\n";

    std::vector<TDefConstructor> two{{"Africa",8}, {"Asia",22}, {"Europe",3}, {"NorthAmerica",4}};
    Print("Contents of vector two before removing anything", two);

    two.erase(two.begin());
    Print("Contents of vector two after removing first element", two);

    two.erase(two.end());
    Print("Contents of vector two after removing end() element", two);
}

void InsertionDuringIteration()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Addtion while iteration tests\n";

    std::vector<TDefConstructor> continents{{"Africa",8}, {"Asia",22}, {"Europe",3}, {"NorthAmerica",4}};
    auto initContinents = continents;
    Print("Contents of vector continents before adding anything", continents);

    auto insertItems = std::vector<std::pair<TDefConstructor,TDefConstructor>>{{{"Asia",22}        ,{"SouthAmerica",543}}
                                                                             , {{"Africa",8}       ,{"Antarctica",3242}}
                                                                             , {{"NorthAmerica",4} ,{"Australia", 392}} };

    // Test 1: Insert items during iteration before the searched items
    for (const auto& it2insert: insertItems)
    {
        for (auto it=continents.begin(); it!=continents.end(); ++it)
        {
            if (*it == it2insert.first)
            {
                // Update the iterator after the insertion
                it = continents.insert(it, it2insert.second);
                // Advance it by one item inorder not to keep always comparing the same item
                std::advance(it,1);
            }
        }
    }
    Print("Test1: Inserting new elements before searched items", continents);

    // Test 2: Insert items during iteration after the searched items
    continents = initContinents;
    for (const auto& it2insert: insertItems)
    {
        for (auto it=continents.begin(); it!=continents.end(); ++it)
        {
            if (*it == it2insert.first)
            {
                // Update the iterator after the insertion
                it = continents.insert(it+1, it2insert.second);
            }
        }
    }
    Print("Test2: Inserting new elements after searched items", continents);
}

void DeletionDuringIteration()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Deletion of items while iteration tests\n";

    std::vector<TDefConstructor> continents{{"Africa",8}, {"SouthAmerica",543}, {"Asia",22}, {"Antarctica",3242}, {"Australia", 392}, {"Europe",3}, {"NorthAmerica",4}};
    auto initContinents = continents;
    Print("Contents of vector continents before adding anything", continents);

    auto items2delete = std::vector<TDefConstructor>{{"Asia",22}, {"Africa",8}, {"NorthAmerica",4}};

    // Test 1: Insert items during iteration before the searched items
    for (const auto& delItem: items2delete)
    {
        for (auto it=continents.begin(); it!=continents.end(); ++it)
        {
            if (*it == delItem)
            {
                // Iterators (including the end() iterator) and references to the 
                // elements at or after the point of the erase are invalidated.
                it = continents.erase(it);
            }
        }
    }
    Print("Test1: After deletion operation", continents);
}

void SimpleInsertionTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Simple iteration tests\n";
    std::vector<int> test {1,2,3,4,5,6,7,8,9,10};
    Print("Original vector", test);

    std::cout << "Size=" << test.size() << ", capacity=" << test.capacity() << std::endl;

    test.insert(test.begin()+3, 437);
    Print("After inserting one element", test);

    test.insert(test.begin(), {999,888,777,666});
    Print("Insert at the beginning with a initializer list of items", test);

    std::vector<int> insertVec = {111,222,333,444,555};
    test.insert(test.begin()+6, insertVec.begin(), insertVec.end()-3);
    Print("Insert another vector elements", test);
}

void IndexBasedIterationAndInsertion()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Index based iteration and insertion\n";
    std::vector<int> test{1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    for (auto i=0; i<test.size(); ++i)
    {
        auto& curVal = test[i];
        std::cout << "curVal=" << curVal << std::endl;
        if (curVal%2==0) // Is even
        {
            test.insert(test.begin()+i, 0);
            ++i; // move to the next element to compensate for the newly added element
        }
    }
    Print("After inserting new elements", test);
}

int main()
{
    InitTests();
    InsertionTests();
    FindTests();
    RemovalTests();
    SimpleInsertionTests();

    // Dangerous usage of insertions using iterators. Potentially leads to invalidated iterators as long as the 
    // following rule is not ensured: "If after the operation the new size() is greater than old capacity() 
    // a reallocation takes place, in which case all iterators (including the end() iterator) and all 
    // references to the elements are invalidated. "
    InsertionDuringIteration();
    // The following example will lead to a crash sometimes because: Iterators (including the end() iterator) 
    // and references to the elements at or after the point of the erase are invalidated.
    //DeletionDuringIteration();

    // Instead use the following safe method of inserting elements while iterating. Again this is quite inefficient.
    // Should be used in rare cases. If one needs to do such operations on bigger vectors, means the choice of the 
    // data structure or the very algorithm where such insertions are required should be questioned. 
    IndexBasedIterationAndInsertion();
    return 0;
}

