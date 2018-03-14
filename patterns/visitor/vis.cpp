#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

enum class Has
{
  Yes,
  No,
  Sometimes
};

struct Humans;
struct Animals;
struct Plants;

struct Visitor
{
  virtual void Visit(Humans*) = 0;
  virtual void Visit(Animals*) = 0;
  virtual void Visit(Plants*) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// A simple hierarchy of classes that need to remain intact without any changes.
// Meaning no further implementation is possible for what ever reason. 
// But it should still be ready for any extensions in functionality.
//////////////////////////////////////////////////////////////////////////////////

struct Being
{
  virtual Has hasLegs() const = 0; // This is the only implementation that is implemented
  virtual void Accept(Visitor*) = 0;
};

struct Humans : public Being
{
  virtual Has hasLegs() const { return Has::Yes; }
  virtual void Accept(Visitor* pV) { pV->Visit(this); }
};

struct Animals : public Being
{
  virtual Has hasLegs() const { return Has::Yes; }
  virtual void Accept(Visitor* pV) { pV->Visit(this); }
};

struct Plants: public Being
{
  virtual Has hasLegs() const { return Has::No; }
  virtual void Accept(Visitor* pV) { pV->Visit(this); }
};

struct GenerateFood : public Visitor
{
  virtual void Visit(Humans*) { std::cout << "Humans can raise their own food" << std::endl; }
  virtual void Visit(Animals*) { std::cout << "Animals cannot raise their own food" << std::endl; }
  virtual void Visit(Plants*) { std::cout << "Plants create their own food" << std::endl; }
};

struct ArmsDescriptor : public Visitor
{
  virtual void Visit(Humans*) { std::cout << "Humans have arms" << std::endl; }
  virtual void Visit(Animals*) { std::cout << "Some animals have arms" << std::endl; }
  virtual void Visit(Plants*) { std::cout << "Plants do not have any arms" << std::endl; }
};

struct Pets : public Visitor
{
  virtual void Visit(Humans*) { std::cout << "Humans cannot be held as Pets" << std::endl; }
  virtual void Visit(Animals*) { std::cout << "Some animals can be held as Pets" << std::endl; }
  virtual void Visit(Plants*) { std::cout << "Not all plants grow every where but many plants are raised at home" << std::endl; }
};


int main()
{
  GenerateFood food;
  ArmsDescriptor arms;
  Pets pets;

  std::vector<std::unique_ptr<Being> > allBeings;
  allBeings.push_back( std::unique_ptr<Being>(new Humans ));
  allBeings.push_back( std::unique_ptr<Being>(new Animals ));
  allBeings.push_back( std::unique_ptr<Being>(new Plants));

  std::for_each(std::begin(allBeings), std::end(allBeings), [&food, &arms, &pets](const std::unique_ptr<Being>& p) {
      p->Accept(&food);
      p->Accept(&arms);
      p->Accept(&pets); });

  return 0;
}

