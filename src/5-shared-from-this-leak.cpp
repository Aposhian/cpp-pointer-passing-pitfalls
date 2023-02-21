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
  void init()
  {
    inside_ = std::make_unique<Inside>(shared_from_this());
  }

  ~Outside() {
    std::cout << "Outside destroyed" << std::endl;
  }

private:
  std::unique_ptr<Inside> inside_;
};

int main()
{
  auto outside = std::make_shared<Outside>();
  std::cout << "before init() ref count: " << outside.use_count() << std::endl;
  outside->init();
  std::cout << "after init() ref count: " << outside.use_count() << std::endl;
  return 0;
}
