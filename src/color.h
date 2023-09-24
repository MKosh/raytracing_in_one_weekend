#pragma once

#include "vec3.h"

#include <iostream>

using color = vec3<double>;

inline auto write_color(std::ostream& out, color pixel_color) -> void {
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
} 
