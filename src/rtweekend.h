#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

namespace rt {
// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653589732385;


// Utility functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double radians_to_degrees(double radians) {
  return radians * 180.0 / pi;
}

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double(double min, double max) {
  return min + (max-min) * random_double();
}

}

#include "interval.h"
#include "ray.h"
#include "vec3.h"
