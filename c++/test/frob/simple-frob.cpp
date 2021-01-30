
#include "doctest.h"

#include "Frob.h"

using namespace frob;



TEST_CASE("frobnicate") {
  uint8_t a = 2;
  uint32_t b = 3;
  uint8_t c = 5;
  uint16_t d = 7;
  double e = 11;
  double f = 13;
  double g = 17;
  double h = 19;

  Frob frob{a, b, c, d, e, f, g, h};
  auto result = frob.frobnicate(23, 29);

  CHECK(282 == result);
}


