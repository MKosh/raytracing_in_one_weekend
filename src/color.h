#pragma once

#include "vec3.h"

#include <iostream>

template<typename T>
using color = vec3<T>;

template<typename T>
inline auto write_color(std::ostream& out, color<T> pixel_color) -> void {
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
} 
