#include <iostream>
#include <list>
#include <string>
#include <ostream>
#include <algorithm>

template <typename T>
void Print(const std::string& s, const std::list<T>& vToPrint)
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
    std::list<int> one(3);  // Create a list with 3 items initially
    Print("Size initialization of list<int> with 3 items", one);

    std::list<int> two{1,2,3,4,5,6,7,8};
    Print("Initialization of list<int> with initilizer list", two);
}

void MergeTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Merge tests\n";
    std::list<int> one{1,2,3,4,5,6};
    std::list<int> two{7,8,9,10,11,12,13};
    std::list<int> three{3,24,1,3,8,2,5};

    // Merge operation 1
    // Note a precondition for successful merge operation is that both the lists
    // should be correctly sorted
    one.merge(two);
    Print("After merge, one", one);
    Print("After merge, two", two);

    // Merge operation 2
    // Note that the list 'three' is not sorted. Regardless of the output, this operation
    // is undefined.
    one.merge(three);
    Print("After merge, one", one);
    Print("After merge, three", three);
}

void SpliceTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Splice tests\n";
    std::list<int> one{1,2,3,4,5,6};
    std::list<int> two{13,7,10,8,12,9,11};

    // Splice operation 1
    one.splice(one.end(), two, std::begin(two));
    Print("After splice operation of one element only, one", one);
    Print("After splice operation of one element only, two", two);

    // Splice operation 2
    auto it = two.begin();
    std::advance(it,2);
    one.splice(one.end(), two, two.begin(), it);
    Print("After splice operation of multiple elements, one", one);
    Print("After splice operation of multiple eleents, two", two);

    // Splice operation 3
    two.reverse();
    Print("Reversed container two", two);
    one.splice(one.end(), two);
    Print("After splice operation of all elements of other container, one", one);
    Print("After splice operation of all elements of other container, two", two);
}

void UniqueTests()
{
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Unique tests\n";
    std::list<int> sorted_sequential{1,2,3,3,3,4,5,5,5,6};
    std::list<int> sorted_nonsequential{1,2,3,4,5,3,3,4,5,5,5,6};
    std::list<int> unsorted_sequential{13,13,13,7,10,10,10,10,8,12,9,11};
    std::list<int> unsorted_nonsequential{13,7,10,8,10,12,9,12,10,10,12,9,11};

    // Operation 1
    Print("Before unique operation, sorted_sequential", sorted_sequential);
    sorted_sequential.unique();
    Print("After unique operation, sorted_sequential", sorted_sequential);

    // Operation 2
    Print("Before unique operation, sorted_nonsequential", sorted_nonsequential);
    sorted_nonsequential.unique();
    Print("After unique operation, sorted_nonsequential", sorted_nonsequential);

    // Operation 3
    Print("Before unique operation, unsorted_sequential", unsorted_sequential);
    unsorted_sequential.unique();
    Print("After unique operation, unsorted_sequential", unsorted_sequential);

    // Operation 4
    Print("Before unique operation, unsorted_nonsequential", unsorted_nonsequential);
    unsorted_nonsequential.unique();
    Print("After unique operation, unsorted_nonsequential", unsorted_nonsequential);
}

int main()
{
    InitTests();
    MergeTests();
    SpliceTests();
    UniqueTests();
    return 0;
}

