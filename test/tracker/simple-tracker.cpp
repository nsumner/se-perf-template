
#include "doctest.h"

#include "Tracker.h"

using namespace tracker;


static bool
returnsTrue(Location loc) {
  return true;
}


TEST_CASE("single") {
  EntityTracker tracker;
  Location loc{0,0};
  std::string name{"Finn"};
  ActionPlan plan = { .secretPlan={0, 1, 2, 3, 4} };

  tracker.addEntity(loc, name, plan);

  size_t dangerous = tracker.countDangerous(returnsTrue);
  CHECK(1 == dangerous);

  bool hasThree = true;
  auto checkThree = [&hasThree] (auto& plan) {
    hasThree &= plan.secretPlan[3] == 3;
  };
  tracker.checkPlans(checkThree);
  CHECK(hasThree);
}


