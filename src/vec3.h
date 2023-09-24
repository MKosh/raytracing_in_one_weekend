#pragma once

// #include <__concepts/arithmetic.h>
#include <cmath>
#include <concepts>
#include <iostream>

using std::sqrt;

template<typename T, typename S>
concept numerals= (std::integral<T> || std::floating_point<T>) && (std::integral<S> || std::floating_point<S>);

template<typename T>
concept numeric = (std::integral<T> || std::floating_point<T>);

// template<typename T, typename S>
// concept numeric_and_float = (std::integral<T> || std::floating_point<T>) && (std::floating_point<S>); 

template <typename T = double>
requires numeric<T>
class vec3 {
public:
  T e[3]; // Three elements
  vec3() : e{0,0,0} {}
  vec3(T e0, T e1, T e2) : e{e0, e1, e2}{}

  auto x() const -> T { return e[0]; }
  auto y() const -> T { return e[1]; }
  auto z() const -> T { return e[2]; }

  auto operator-() const -> vec3 { return vec3(-e[0], -e[1], -e[2]); }
  auto operator[](int i) const -> T { return e[i]; }
  auto operator[](int i) -> T& { return e[i]; }

  operator vec3<float>() const {
    vec3<float> f;
    f.e[0] = static_cast<float>(e[0]);
    f.e[1] = static_cast<float>(e[1]);
    f.e[2] = static_cast<float>(e[2]);
    return f;
  }
  
  operator vec3<int>() const {
    vec3<int> i;
    i.e[0] = static_cast<float>(e[0]);
    i.e[1] = static_cast<float>(e[1]);
    i.e[2] = static_cast<float>(e[2]);
    return i;
  }

  operator vec3<double>() const {
    vec3<double> d;
    d.e[0] = static_cast<double>(e[0]);
    d.e[1] = static_cast<double>(e[1]);
    d.e[2] = static_cast<double>(e[2]);
    return d;
  }

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

using point3 = vec3<double>;

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const vec3<T>& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator+(const vec3<T>& u, const vec3<S>& v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator-(const vec3<T>& u, const vec3<S>& v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator*(const vec3<T>& u, const vec3<S>& v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator*(const vec3<T>& u, S s) {
  return vec3(u.e[0] * s, u.e[1] * s, u.e[2] * s);
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator*(S s, const vec3<T>& u) {
  return u * s;
}

template<typename T, typename S>
requires numerals<T, S>
inline auto operator/(const vec3<T>& u, S s) {
  return (1.0/s) * u;
}

template<typename T, typename S>
requires numerals<T, S>
inline auto dot(const vec3<T>& u, const vec3<S>& v) {
  return (u.e[0] * v.e[0] +
          u.e[1] * v.e[1] +
          u.e[2] * v.e[2]);
}

template<typename T, typename S>
requires numerals<T, S>
inline auto cross(const vec3<T>& u, const vec3<S>& v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

template<typename T>
requires numeric<T>
inline auto unit_vector(const vec3<T> v) {
  return v/v.length();
}
