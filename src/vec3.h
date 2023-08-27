#pragma once

#include <cmath>
#include <concepts>
#include <iostream>

using std::sqrt;

template <typename T = double>
requires std::integral<T> || std::floating_point<T>
class vec3 {
public:
  T e[3];
  vec3() : e{0,0,0} {}
  vec3(T e0, T e1, T e2) : e{e0, e1, e2}{}

  auto x() const -> T { return e[0]; }
  auto y() const -> T { return e[1]; }
  auto z() const -> T { return e[2]; }

  auto operator-() const -> vec3 { return vec3(-e[0], -e[1], -e[2]); }
  auto operator[](int i) const -> T { return e[i]; }
  auto operator[](int i) -> T& { return e[i]; }

  auto operator+=(const vec3& v) -> vec3& {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  
  auto operator*=(double t) -> vec3& {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  auto operator/=(double t) -> vec3& {
    return *this *= 1/t;
  }

  auto length() const -> double {
    return sqrt(length_squared());
  }

  auto length_squared() const -> double {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
  }

};

template<typename T>
using point3 = vec3<T>;

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const vec3<T>& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}