#include <memory>
#include <iostream>

class Outside;

class Inside
{
public:
  Inside(std::weak_ptr<Outside> outside)
  : outside_(outside) {}

  void use()
  {
    auto shared = outside_.lock();
    std::cout << "during use() ref count: " << shared.use_count() << std::endl;
  }

private:
  std::weak_ptr<Outside> outside_;
};

class Outside : public std::enable_shared_from_this<Outside>
{
public:
  void init()
  {
    inside_ = std::make_unique<Inside>(weak_from_this());
  }

  void use()
  {
    inside_->use();
  }

private:
  std::unique_ptr<Inside> inside_;
};

int main()
{
  auto outside = std::make_shared<Outside>();
  std::cout << "before init() ref count: " << outside.use_count() << std::endl;
  outside->init();
  outside->use();
  std::cout << "after init() ref count: " << outside.use_count() << std::endl;
  return 0;
}
