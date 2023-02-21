#include <memory>
#include <iostream>

class Outside;

class Inside
{
public:
  Inside(std::shared_ptr<Outside> outside)
  : outside_(outside) {}

  ~Inside() {
    std::cout << "Inside destroyed" << std::endl;
  }

private:
  std::shared_ptr<Outside> outside_;
};

class Outside : public std::enable_shared_from_this<Outside>
{
public:
  ~Outside() {
    std::cout << "Outside destroyed" << std::endl;
  }
};

class Owner
{
public:
  Owner()
  : outside_(std::make_shared<Outside>()),
    inside_(outside_)
  {
  }

private:
  std::shared_ptr<Outside> outside_;
  Inside inside_;
};

int main()
{
  Owner owner;
  return 0;
}
