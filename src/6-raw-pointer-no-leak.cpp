#include <memory>

class Outside;

class Inside
{
public:
  Inside(Outside * const outside)
  : outside_(outside) {}

private:
  Outside * const outside_;
};

class Outside
{
public:
  Outside()
  : inside_(this) {}

private:
  Inside inside_;
};

int main()
{
  Outside outside;
  return 0;
}
