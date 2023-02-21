#include <iostream>

class Outside;

class Inside
{
public:
  Inside(Outside& outside)
  : outside_(outside) {}

  ~Inside() {
    std::cout << "Inside destroyed" << std::endl;
  }

private:
  Outside& outside_;
};

class Outside
{
public:
  Outside()
  : inside_(*this) {}

  ~Outside() {
    std::cout << "Outside destroyed" << std::endl;
  }

private:
  Inside inside_;
};

int main()
{
  Outside outside;
  return 0;
}
