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
  void init()
  {
    inside_ = std::make_unique<Inside>(shared_from_this());
  }

private:
  std::unique_ptr<Inside> inside_;
};

int main()
{
  Outside outside;
  // This will throw
  outside.init();
  return 0;
}
