#pragma once

#include "vec3.h"

// template<typename T>
// requires numeric<T>
class ray {
public:
  ray() {}

  ray(const point3& origin, const vec3<double>& direction) : orig(origin), dir(direction) {}

  auto origin() const -> point3 { return orig; }
  auto direction() const -> vec3<double> { return dir; }

  auto at(double t) const -> point3 {
    return orig + t * dir;
  }

private:
  point3 orig;
  vec3<double> dir;
};
