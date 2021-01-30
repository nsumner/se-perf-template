#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>
#include <deque>


namespace tracker {


// A simple struct maintaining coordinate locations in an xy-plane.
struct Location {
  uint32_t x;
  uint32_t y;
};


struct ActionPlan {
  std::array<uint8_t,512> secretPlan;
};


// Entities comprise Locations, names, and a plan of action that may contain
// specific, sensitive data.
struct Entity {
  Location location;
  std::string_view name;
  ActionPlan plan;
};


class EntityTracker {
public:
  void
  addEntity(Location location, std::string_view name, const ActionPlan& plan) {
    entities.push_back({location, name, plan});
  }

  template<class IsDangerous>
  size_t
  countDangerous(IsDangerous& isDangerous) {
    size_t count = 0;
    for (const auto& entity : entities) {
      if (isDangerous(entity.location)) {
        count = count + 1;
      }
    }
    
    return count;
  }

  template<class Check>
  void
  checkPlans(Check& check) {
    for (const auto& entity : entities) {
      check(entity.plan);
    }
  }

private:
  std::vector<Entity> entities;
};


}

