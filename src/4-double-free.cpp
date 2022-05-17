#include <memory>

class Outside;

class Inside
{
public:
  Inside(std::shared_ptr<Outside> outside)
  : outside_(outside) {}

private:
  std::shared_ptr<Outside> outside_;
};

class Outside
{
public:
  Outside()
  : inside_(std::shared_ptr<Outside>(this)) {}

private:
  Inside inside_;
};

int main()
{
  Outside outside;
  return 0;
}
