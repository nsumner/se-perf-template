#pragma once


#include <cstdint>
#include <vector>


namespace executor {


class Task {
public:
  virtual ~Task() = default;

  void doTask() { doTaskImpl(); }
private:
  virtual void doTaskImpl() = 0;
};


// A simple incrementer task
class Task1 final : public Task {
public:
  Task1(uint32_t& toIncrement)
    : toIncrement{toIncrement}
      { }

private:
  void
  doTaskImpl() override {
    toIncrement += 1;
  }

  uint32_t& toIncrement;
};


// A simple decrementer task
class Task2 final : public Task {
public:
  Task2(uint32_t& toDecrement)
    : toDecrement{toDecrement}
      { }

private:
  void
  doTaskImpl() override {
    toDecrement -= 1;
  }

  uint32_t& toDecrement;
};


// A deluxe incrementer task, sold at a premium to the client
class Task3 final : public Task {
public:
  Task3(uint32_t& toIncrement)
    : toIncrement{toIncrement}
      { }

private:
  virtual void
  doTaskImpl() {
    toIncrement += 2;
  }

  uint32_t& toIncrement;
};


// The Executor must execute the passed in work whenever execute is called.
class Executor {
public:
  explicit Executor(const std::vector<Task*>& tasks)
    : tasks{tasks}
      { }
  
  void
  execute() {
    for (auto* task : tasks) {
      task->doTask();
    }
  }

private:
  const std::vector<Task*>& tasks;
};


}

