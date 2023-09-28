#pragma once

#include "rtweekend.h"
class interval {
public:
  double min, max;

  interval() : min(+rt::infinity), max(-rt::infinity) {} // Default interval is empty

  interval(double _min, double _max) : min(_min), max(_max) {}

  auto contains(double x) const -> bool {
    return min <= x && x <= max;
  }

  auto surrounds(double x) const -> bool {
    return min < x && x < max;
  }

  static const interval empty, universe;
};

const static interval empty    (+rt::infinity, -rt::infinity);
const static interval universe (-rt::infinity, +rt::infinity);
