
#include "doctest.h"

#include "Tracker.h"

using namespace tracker;


static bool
returnsTrue(Location /*loc*/) {
  return true;
}


static bool
containsZero(Location loc) {
  return loc.x == 0 || loc.y == 0;
}


TEST_CASE("single entity") {
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


TEST_CASE("multiple entities") {
  EntityTracker tracker;

  Location loc1{0,0};
  std::string name1{"Finn"};
  ActionPlan plan1 = { .secretPlan={0, 1, 2, 3, 4} };
  tracker.addEntity(loc1, name1, plan1);

  Location loc2{0,1};
  std::string name2{"Jake"};
  ActionPlan plan2 = { .secretPlan={4, 3, 2, 1, 0} };
  tracker.addEntity(loc2, name2, plan2);

  Location loc3{1,0};
  std::string name3{"Lady Rainicorn"};
  ActionPlan plan3 = { .secretPlan={3, 2, 1, 0, 4} };
  tracker.addEntity(loc3, name3, plan3);

  size_t dangerous = tracker.countDangerous(returnsTrue);
  CHECK(3 == dangerous);

  bool hasThree = true;
  auto checkAllThree = [&hasThree] (auto& plan) {
    hasThree &= plan.secretPlan[3] == 3;
  };
  tracker.checkPlans(checkAllThree);
  CHECK(!hasThree);

  hasThree = false;
  auto checkAnyThree = [&hasThree] (auto& plan) {
    hasThree |= plan.secretPlan[3] == 3;
  };
  tracker.checkPlans(checkAnyThree);
  CHECK(hasThree);
}


TEST_CASE("Mix of dangerousness") {
  EntityTracker tracker;

  Location loc1{0,0};
  std::string name1{"Finn"};
  ActionPlan plan1 = { .secretPlan={0, 1, 2, 3, 4} };
  tracker.addEntity(loc1, name1, plan1);

  Location loc2{0,1};
  std::string name2{"Jake"};
  ActionPlan plan2 = { .secretPlan={4, 3, 2, 1, 0} };
  tracker.addEntity(loc2, name2, plan2);

  Location loc3{1,0};
  std::string name3{"Lady Rainicorn"};
  ActionPlan plan3 = { .secretPlan={3, 2, 1, 0, 4} };
  tracker.addEntity(loc3, name3, plan3);

  size_t dangerous = tracker.countDangerous(containsZero);
  CHECK(3 == dangerous);
}


TEST_CASE("Different forms of dangerousness") {
  EntityTracker tracker;

  Location loc1{0,0};
  std::string name1{"Finn"};
  ActionPlan plan1 = { .secretPlan={0, 1, 2, 3, 4} };
  tracker.addEntity(loc1, name1, plan1);

  Location loc2{0,1};
  std::string name2{"Jake"};
  ActionPlan plan2 = { .secretPlan={4, 3, 2, 1, 0} };
  tracker.addEntity(loc2, name2, plan2);

  Location loc3{1,0};
  std::string name3{"Lady Rainicorn"};
  ActionPlan plan3 = { .secretPlan={3, 2, 1, 0, 4} };
  tracker.addEntity(loc3, name3, plan3);

  size_t dangerous = tracker.countDangerous(containsZero);
  CHECK(3 == dangerous);

  dangerous = tracker.countDangerous(returnsTrue);
  CHECK(3 == dangerous);

  auto containsOne = [](auto& loc) -> bool {
    return loc.x == 1 || loc.y == 1;
  };
  dangerous = tracker.countDangerous(containsOne);
  CHECK(2 == dangerous);
}

