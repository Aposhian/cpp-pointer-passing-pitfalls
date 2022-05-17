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

class Outside : public std::enable_shared_from_this<Outside>
{
public:
  Outside()
  : inside_(shared_from_this()) {}

private:
  Inside inside_;
};

int main()
{
  // This will throw
  auto outside = std::shared_ptr<Outside>();
  return 0;
}
