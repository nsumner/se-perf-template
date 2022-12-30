
#include "doctest.h"

#include "Executor.h"

using namespace executor;



TEST_CASE("one of each") {
  uint32_t t1val = 0;
  uint32_t t2val = 0;
  uint32_t t3val = 0;
  Task1 t1{t1val};
  Task2 t2{t2val};
  Task3 t3{t3val};
  std::vector<Task*> tasks = { &t1, &t2, &t3 };
  Executor executor{tasks};

  executor.execute();

  CHECK(1 == t1val);
  CHECK(uint32_t(-1) == t2val);
  CHECK(2 == t3val);
}


class Task4 final : public Task {
public:
  Task4(uint32_t& toIncrement)
    : Task{this},
      toIncrement{toIncrement}
      { }

private:
  virtual void
  doTaskImpl() {
    toIncrement += 5;
  }

  uint32_t& toIncrement;
};


TEST_CASE("new tasks added") {
  uint32_t t4val = 0;
  Task4 t4{t4val};
  std::vector<Task*> tasks = { &t4 };
  Executor executor{tasks};

  executor.execute();

  CHECK(5 == t4val);
}


TEST_CASE("Repeated executions") {
  uint32_t t1val = 0;
  uint32_t t2val = 0;
  uint32_t t3val = 0;
  uint32_t t4val = 0;
  Task1 t1{t1val};
  Task2 t2{t2val};
  Task3 t3{t3val};
  Task4 t4{t4val};
  std::vector<Task*> tasks = { &t1, &t2, &t3, &t4 };
  Executor executor{tasks};

  executor.execute();

  CHECK(1 == t1val);
  CHECK(uint32_t(-1) == t2val);
  CHECK(2 == t3val);
  CHECK(5 == t4val);

  executor.execute();

  CHECK(2 == t1val);
  CHECK(uint32_t(-2) == t2val);
  CHECK(4 == t3val);
  CHECK(10 == t4val);
}


