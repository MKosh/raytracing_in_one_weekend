#pragma once

#include "vec3.h"

template<typename T>
requires numeric<T>
class ray {
public:
  ray() {}

  ray(const point3<T>& origin, const vec3<T>& direction) : orig(origin), dir(direction) {}

  auto origin() const -> point3<T> { return orig; }
  auto direction() const -> vec3<T> { return dir; }

  auto at(T t) const -> point3<T> {
    return orig + t * dir;
  }

private:
  point3<T> orig;
  vec3<T> dir;
};
