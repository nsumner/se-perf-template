
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


