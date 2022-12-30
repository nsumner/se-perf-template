#pragma once


#include <cstdint>
#include <memory>


namespace frob {


class Frob {
public:
  Frob(uint8_t a, uint32_t b, uint8_t c, uint16_t d, double e, double f, double g, double h)
    : wizzle{std::make_unique<Wizzle>(a, d, e, f)},
      wazzle{std::make_unique<Wazzle>(b, c, g, h)}
      { }
  
  uint32_t frobnicate(uint32_t first, uint32_t second) const {
    return getA()*getB()*first + getD()*getA()*getC() + getB()*getB()*getC() + second;
  }

  uint8_t  getA() const { return wizzle->getA(); }
  uint32_t getB() const { return wazzle->getB(); }
  uint8_t  getC() const { return wazzle->getC(); }
  uint16_t getD() const { return wizzle->getD(); }
  double   getE() const { return wizzle->getE(); }
  double   getF() const { return wizzle->getF(); }
  double   getG() const { return wazzle->getG(); }
  double   getH() const { return wazzle->getH(); }

private:

  class Wizzle {
  public:
    using Woozle = std::pair<uint8_t, double>;
    using Wuuzle = std::pair<uint16_t, double>;

    Wizzle(uint8_t a, uint16_t d, double e, double f)
      : woozle{std::make_unique<Woozle>(a, e)},
        wuuzle{std::make_unique<Wuuzle>(d, f)}
        { }
    
    uint8_t  getA() const { return woozle->first; }
    uint16_t getD() const { return wuuzle->first; }
    double   getE() const { return woozle->second; }
    double   getF() const { return wuuzle->second; }

    std::unique_ptr<Woozle> woozle;
    std::unique_ptr<Wuuzle> wuuzle;
  };
  
  class Wazzle {
  public:
    using Fiddle = std::pair<uint32_t, double>;
    using Faddle = std::pair<uint8_t, double>;

    Wazzle(uint32_t b, uint8_t c, double g, double h)
      : fiddle{std::make_unique<Fiddle>(b, g)},
        faddle{std::make_unique<Faddle>(c, h)}
        { }
    
    uint32_t getB() const { return fiddle->first; }
    uint8_t  getC() const { return faddle->first; }
    double   getG() const { return fiddle->second; }
    double   getH() const { return faddle->second; }

    std::unique_ptr<Fiddle> fiddle;
    std::unique_ptr<Faddle> faddle;
  };
  

  std::unique_ptr<Wizzle> wizzle;
  std::unique_ptr<Wazzle> wazzle;
};


}

