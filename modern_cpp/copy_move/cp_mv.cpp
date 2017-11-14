// http://coliru.stacked-crooked.com/a/7d780ac6ad77bd95

#include <iostream>
#include <list>

class DeepClass
{
  public:
    DeepClass(const std::string _name, const std::size_t n, const int seed)
      : name(_name)
    {
      for (std::size_t i=0; i<n; ++i)
      {
        l.push_back(seed * i);
      }
    }

    DeepClass(const DeepClass& rhs)
    {
      std::cout << "In copy constructor" << std::endl;
      name = rhs.name;
    }

    DeepClass(DeepClass&& rhs)
    {
      std::cout << "In move constructor" << std::endl;
      name = std::move(rhs.name);
      l = std::move(rhs.l);
    }

    DeepClass& operator=(const DeepClass& rhs)
    {
      std::cout << "In copy assignment operator" << std::endl;
      name = rhs.name;
      return *this;
    }

    DeepClass& operator=(DeepClass&& rhs)
    {
      std::cout << "In move assignment operator" << std::endl;
      name = std::move(rhs.name);
      l = std::move(rhs.l);
      return *this;
    }

    void Print() const
    {
      std::cout << name << ": ";
      for (auto p : l) { std::cout << p << " "; }
      std::cout << std::endl << std::endl;
    }

  private:
    std::string name;
    std::list<int> l;
};

void copy_test()
{
  DeepClass d("Object-d", 12, 2);
  d.Print();

  DeepClass d2("Object-d2", 22, 12);
  d2.Print();

  std::cout << "Operation: d=d2" << std::endl;
  d = d2; // call copy assignment operator
  d.Print();
  d2.Print();

  std::cout << "Operation: DeepClass d3(d2)" << std::endl;
  DeepClass d3(d2); // call copy constructor
  d3.Print();
  d2.Print();
}

void move_test()
{
  DeepClass d("Object-d", 12, 2);
  d.Print();

  DeepClass d2("Object-d2", 22, 12);
  d2.Print();

  DeepClass d3("Object-d3", 10, 17);
  d3.Print();

  std::cout << "Operation: d=std::move(d2)" << std::endl;
  d = std::move(d2); // call copy assignment operator
  d.Print();
  d2.Print();

  std::cout << "Operation: DeepClass d4(std::move(d3))" << std::endl;
  DeepClass d4(std::move(d3)); // call copy constructor
  d3.Print();
  d4.Print();
}

int main()
{
  std::cout << "COPY TESTS ...." << std::endl;
  copy_test();

  std::cout << std::endl << "MOVE TESTS ...." << std::endl;
  move_test();

  return 0;
}



