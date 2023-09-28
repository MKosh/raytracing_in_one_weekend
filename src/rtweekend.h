#pragma once

#include <cmath>
#include <limits>
#include <memory>

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
}

#include "interval.h"
#include "ray.h"
#include "vec3.h"
